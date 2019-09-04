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
struct TYPE_2__ {int bStatus; scalar_t__ ulCapClass; scalar_t__ ucCardType; int usRCA; } ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ CARD_CAP_CLASS_SDSC ; 
 scalar_t__ CARD_TYPE_SDCARD ; 
 int /*<<< orphan*/  CMD_APP_CMD ; 
 int /*<<< orphan*/  CMD_SET_BLK_CNT ; 
 int /*<<< orphan*/  CMD_STOP_TRANS ; 
 int /*<<< orphan*/  CMD_WRITE_MULTI_BLK ; 
 int /*<<< orphan*/  CMD_WRITE_SINGLE_BLK ; 
 scalar_t__ CardSendCmd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SDHostBlockCountSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SDHostDataWrite (int /*<<< orphan*/ ,unsigned long) ; 
 int MAP_SDHostIntStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RES_ERROR ; 
 int /*<<< orphan*/  RES_NOTRDY ; 
 int /*<<< orphan*/  RES_OK ; 
 int /*<<< orphan*/  SDHOST_BASE ; 
 int SDHOST_INT_TC ; 
 int SD_SECTOR_SIZE ; 
 int STA_NOINIT ; 
 TYPE_1__ sd_disk_info ; 

DRESULT sd_disk_write (const BYTE* pBuffer, DWORD ulSectorNumber, UINT SectorCount) {
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
            // Send single block write command
            if (CardSendCmd(CMD_WRITE_SINGLE_BLK, ulSectorNumber) == 0) {
                // Write the data
                while (ulSize--) {
                    MAP_SDHostDataWrite (SDHOST_BASE, (*(unsigned long *)pBuffer));
                    pBuffer += 4;
                }
                // Wait for data transfer complete
                while (!(MAP_SDHostIntStatus(SDHOST_BASE) & SDHOST_INT_TC));
                Res = RES_OK;
            }
        }
        else {
            // Set the card write block count
            if (sd_disk_info.ucCardType == CARD_TYPE_SDCARD) {
                CardSendCmd(CMD_APP_CMD,sd_disk_info.usRCA << 16);
                CardSendCmd(CMD_SET_BLK_CNT, SectorCount);
            }

            // Send multi block write command
            if (CardSendCmd(CMD_WRITE_MULTI_BLK, ulSectorNumber) == 0) {
                // Write the data buffer
                while (ulSize--) {
                    MAP_SDHostDataWrite(SDHOST_BASE, (*(unsigned long *)pBuffer));
                    pBuffer += 4;
                }
                // Wait for transfer complete
                while (!(MAP_SDHostIntStatus(SDHOST_BASE) & SDHOST_INT_TC));
                CardSendCmd(CMD_STOP_TRANS, 0);
                while (!(MAP_SDHostIntStatus(SDHOST_BASE) & SDHOST_INT_TC));
                Res = RES_OK;
            }
        }
    }

    return Res;
}