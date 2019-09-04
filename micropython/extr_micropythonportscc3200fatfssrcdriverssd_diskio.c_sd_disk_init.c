#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bStatus; unsigned long usRCA; void* ucCardType; int /*<<< orphan*/  ulCapClass; int /*<<< orphan*/  ulVersion; } ;
typedef  scalar_t__ DSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_CAP_CLASS_SDHC ; 
 void* CARD_TYPE_MMC ; 
 void* CARD_TYPE_SDCARD ; 
 int /*<<< orphan*/  CARD_VERSION_2 ; 
 int /*<<< orphan*/  CMD_ALL_SEND_CID ; 
 int /*<<< orphan*/  CMD_APP_CMD ; 
 int /*<<< orphan*/  CMD_GO_IDLE_STATE ; 
 int /*<<< orphan*/  CMD_SD_SEND_OP_COND ; 
 int /*<<< orphan*/  CMD_SEND_IF_COND ; 
 int /*<<< orphan*/  CMD_SEND_OP_COND ; 
 int /*<<< orphan*/  CMD_SEND_REL_ADDR ; 
 int /*<<< orphan*/  CardCapacityGet (TYPE_1__*) ; 
 unsigned long CardSelect (TYPE_1__*) ; 
 unsigned long CardSendCmd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAP_SDHostRespGet (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  SDHOST_BASE ; 
 scalar_t__ STA_NODISK ; 
 TYPE_1__ sd_disk_info ; 

DSTATUS sd_disk_init (void) {
    unsigned long ulRet;
    unsigned long ulResp[4];

    if (sd_disk_info.bStatus != 0) {
        sd_disk_info.bStatus = STA_NODISK;
        // Send std GO IDLE command
        if (CardSendCmd(CMD_GO_IDLE_STATE, 0) == 0) {
            // Get interface operating condition for the card
            ulRet = CardSendCmd(CMD_SEND_IF_COND,0x000001A5);
            MAP_SDHostRespGet(SDHOST_BASE,ulResp);

            // It's a SD ver 2.0 or higher card
            if (ulRet == 0 && ((ulResp[0] & 0xFF) == 0xA5)) {
                // Version 1 card do not respond to this command
                sd_disk_info.ulVersion = CARD_VERSION_2;
                sd_disk_info.ucCardType = CARD_TYPE_SDCARD;

                // Wait for card to become ready.
                do {
                    // Send ACMD41
                    CardSendCmd(CMD_APP_CMD, 0);
                    ulRet = CardSendCmd(CMD_SD_SEND_OP_COND, 0x40E00000);

                    // Response contains 32-bit OCR register
                    MAP_SDHostRespGet(SDHOST_BASE, ulResp);

                } while (((ulResp[0] >> 31) == 0));

                if (ulResp[0] & (1UL<<30)) {
                    sd_disk_info.ulCapClass = CARD_CAP_CLASS_SDHC;
                }
                sd_disk_info.bStatus = 0;
            }
            //It's a MMC or SD 1.x card
            else {
                // Wait for card to become ready.
                do {
                    CardSendCmd(CMD_APP_CMD, 0);
                    ulRet = CardSendCmd(CMD_SD_SEND_OP_COND,0x00E00000);
                    if (ulRet == 0) {
                        // Response contains 32-bit OCR register
                        MAP_SDHostRespGet(SDHOST_BASE, ulResp);
                    }
                } while (((ulRet == 0) && (ulResp[0] >> 31) == 0));

                if (ulRet == 0) {
                    sd_disk_info.ucCardType = CARD_TYPE_SDCARD;
                    sd_disk_info.bStatus = 0;
                }
                else {
                    if (CardSendCmd(CMD_SEND_OP_COND, 0) == 0) {
                        // MMC not supported by the controller
                        sd_disk_info.ucCardType = CARD_TYPE_MMC;
                    }
                }
            }
        }

        // Get the RCA of the attached card
        if (sd_disk_info.bStatus == 0) {
            ulRet = CardSendCmd(CMD_ALL_SEND_CID, 0);
            if (ulRet == 0) {
                CardSendCmd(CMD_SEND_REL_ADDR,0);
                MAP_SDHostRespGet(SDHOST_BASE, ulResp);

                //  Fill in the RCA
                sd_disk_info.usRCA = (ulResp[0] >> 16);

                // Get tha card capacity
                CardCapacityGet(&sd_disk_info);
            }

            // Select the card.
            ulRet = CardSelect(&sd_disk_info);
            if (ulRet == 0) {
                sd_disk_info.bStatus = 0;
            }
        }
    }

    return sd_disk_info.bStatus;
}