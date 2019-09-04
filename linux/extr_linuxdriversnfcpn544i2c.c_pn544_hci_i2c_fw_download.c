#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pn544_i2c_phy {int /*<<< orphan*/  fw_work; int /*<<< orphan*/  fw_work_state; int /*<<< orphan*/  hw_variant; int /*<<< orphan*/  firmware_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_WORK_STATE_START ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int pn544_hci_i2c_fw_download(void *phy_id, const char *firmware_name,
					u8 hw_variant)
{
	struct pn544_i2c_phy *phy = phy_id;

	pr_info("Starting Firmware Download (%s)\n", firmware_name);

	strcpy(phy->firmware_name, firmware_name);

	phy->hw_variant = hw_variant;
	phy->fw_work_state = FW_WORK_STATE_START;

	schedule_work(&phy->fw_work);

	return 0;
}