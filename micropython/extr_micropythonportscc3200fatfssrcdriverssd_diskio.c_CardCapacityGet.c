#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int usRCA; unsigned long ulBlockSize; unsigned long ulNofBlock; } ;
typedef  TYPE_1__ DiskInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND_CSD ; 
 unsigned long CardSendCmd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SDHostRespGet (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  SDHOST_BASE ; 
 int SD_SECTOR_SIZE ; 

__attribute__((used)) static unsigned int CardCapacityGet(DiskInfo_t *psDiskInfo) {
    unsigned long ulRet;
    unsigned long ulResp[4];
    unsigned long ulBlockSize;
    unsigned long ulBlockCount;
    unsigned long ulCSizeMult;
    unsigned long ulCSize;

    // Read the CSD register
    ulRet = CardSendCmd(CMD_SEND_CSD, (psDiskInfo->usRCA << 16));

    if(ulRet == 0) {
        // Read the response
        MAP_SDHostRespGet(SDHOST_BASE,ulResp);

        // 136 bit CSD register is read into an array of 4 words.
        // ulResp[0] = CSD[31:0]
        // ulResp[1] = CSD[63:32]
        // ulResp[2] = CSD[95:64]
        // ulResp[3] = CSD[127:96]
        if(ulResp[3] >> 30) {
            ulBlockSize = SD_SECTOR_SIZE * 1024;
            ulBlockCount = (ulResp[1] >> 16 | ((ulResp[2] & 0x3F) << 16)) + 1;
        }
        else {
            ulBlockSize  = 1 << ((ulResp[2] >> 16) & 0xF);
            ulCSizeMult  = ((ulResp[1] >> 15) & 0x7);
            ulCSize      = ((ulResp[1] >> 30) | (ulResp[2] & 0x3FF) << 2);
            ulBlockCount = (ulCSize + 1) * (1 << (ulCSizeMult + 2));
        }

        // Calculate the card capacity in bytes
        psDiskInfo->ulBlockSize = ulBlockSize;
        psDiskInfo->ulNofBlock  = ulBlockCount;
    }

    return ulRet;
}