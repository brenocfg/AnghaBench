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
typedef  int /*<<< orphan*/  u32 ;
struct pn544_i2c_phy {int /*<<< orphan*/  firmware_name; TYPE_1__* hdev; int /*<<< orphan*/ * fw; int /*<<< orphan*/  fw_work_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_WORK_STATE_IDLE ; 
 int /*<<< orphan*/  nfc_fw_download_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn544_hci_i2c_disable (struct pn544_i2c_phy*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pn544_hci_i2c_fw_work_complete(struct pn544_i2c_phy *phy,
					   int result)
{
	pr_info("Firmware Download Complete, result=%d\n", result);

	pn544_hci_i2c_disable(phy);

	phy->fw_work_state = FW_WORK_STATE_IDLE;

	if (phy->fw) {
		release_firmware(phy->fw);
		phy->fw = NULL;
	}

	nfc_fw_download_done(phy->hdev->ndev, phy->firmware_name, (u32) -result);
}