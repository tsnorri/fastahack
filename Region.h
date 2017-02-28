#ifndef FASTA_REGION_H
#define FASTA_REGION_H

#include <string>
#include <stdlib.h>

class FastaRegion {
public:
    std::string startSeq;
    int startPos;
    int stopPos;

    FastaRegion(std::string& region) {
        startPos = -1;
        stopPos = -1;
        size_t foundFirstColon = region.find(":");
        // we only have a single string, use the whole sequence as the target
        if (foundFirstColon == std::string::npos) {
            startSeq = region;
        } else {
            startSeq = region.substr(0, foundFirstColon);
            size_t foundRangeDots = region.find("..", foundFirstColon);
            size_t foundRangeDash = region.find("-", foundFirstColon);
            if (foundRangeDots == std::string::npos && foundRangeDash == std::string::npos) {
                startPos = atoi(region.substr(foundFirstColon + 1).c_str());
                stopPos = startPos; // just print one base if we don't give an end
            } else {
		if (foundRangeDash == std::string::npos) {
		    startPos = atoi(region.substr(foundFirstColon + 1, foundRangeDots - foundRangeDots - 1).c_str());
		    stopPos = atoi(region.substr(foundRangeDots + 2).c_str()); // to the start of this chromosome
		} else {
		    startPos = atoi(region.substr(foundFirstColon + 1, foundRangeDash - foundRangeDash - 1).c_str());
		    stopPos = atoi(region.substr(foundRangeDash + 1).c_str()); // to the start of this chromosome
		}
            }
        }
    }

    int length(void) {
        if (stopPos > 0) {
            return stopPos - startPos + 1;
        } else {
            return 1;
        }
    }

};

#endif
