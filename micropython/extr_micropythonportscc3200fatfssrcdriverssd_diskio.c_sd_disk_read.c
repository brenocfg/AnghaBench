#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_2__ {int bStatus; scalar_t__ ulCapClass; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CARD_CAP_CLASS_SDSC ; 
 int /*<<< orphan*/  CMD_READ_MULTI_BLK ; 
 int /*<<< orphan*/  CMD_READ_SINGLE_BLK ; 
 int /*<<< orphan*/  CMD_STOP_TRANS ; 
 scalar_t__ CardSendCmd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SDHostBlockCountSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SDHostDataRead (int /*<<< orphan*/ ,unsigned long*) ; 
 int MAP_SDHostIntStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_NOTRDY ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  SDHOST_BASE ; 
 int SDHOST_INT_TC ; 
 int SD_SECTOR_SIZE ; 
 int STA_NOINIT ; 
 TYPE_1__ sd_disk_info ; 

DRESULT sd_disk_read (BYTE* pBuffer, DWORD ulSectorNumber, UINT SectorCount) {
    DRESULT Res = RES_ERROR;
    unsigned long ulSize;

    if (SectorCount > 0) {
        // Return if disk not initialized
        if (sd_disk_info.bStatus & STA_NOINIT) {
            return RES_NOTRDY;
        }

        // SDSC uses linear address, SDHC uses block address
        if (sd_disk_info.ulCapClass == CARD_CAP_CLASS_SDSC) {
            ulSectorNumber = ulSectorNumber * SD_SECTOR_SIZE;
        }

        // Set the block count
        MAP_SDHostBlockCountSet(SDHOST_BASE, SectorCount);

        // Compute the number of words
        ulSize = (SD_SECTOR_SIZE * SectorCount) / 4;

        // Check if 1 block or multi block transfer
        if (SectorCount == 1) {
            // Send single block read command
            if (CardSendCmd(CMD_READ_SINGLE_BLK, ulSectorNumber) == 0) {
                // Read the block of data
                while (ulSize--) {
                    MAP_SDHostDataRead(SDHOST_BASE, (unsigned long *)pBuffer);
                    pBuffer += 4;
                }
                Res = RES_OK;
            }
        }
        else {
            // Send multi block read command
            if (CardSendCmd(CMD_READ_MULTI_BLK, ulSectorNumber) == 0) {
                // Read the data
                while (ulSize--) {
                    MAP_SDHostDataRead(SDHOST_BASE, (unsigned long *)pBuffer);
                    pBuffer += 4;
                }
                CardSendCmd(CMD_STOP_TRANS, 0);
                while (!(MAP_SDHostIntStatus(SDHOST_BASE) & SDHOST_INT_TC));
                Res = RES_OK;
            }
        }
    }

    return Res;
}