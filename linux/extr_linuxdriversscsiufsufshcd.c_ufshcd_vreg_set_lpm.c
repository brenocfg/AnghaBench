#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vccq2; int /*<<< orphan*/  vccq; int /*<<< orphan*/  vcc; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_lu_power_on_wp; } ;
struct ufs_hba {int dev_quirks; TYPE_1__ vreg_info; int /*<<< orphan*/  dev; TYPE_2__ dev_info; } ;

/* Variables and functions */
 int UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM ; 
 int /*<<< orphan*/  ufshcd_config_vreg_lpm (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_is_link_active (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_link_off (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_is_ufs_dev_active (struct ufs_hba*) ; 
 scalar_t__ ufshcd_is_ufs_dev_poweroff (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_setup_vreg (struct ufs_hba*,int) ; 
 int /*<<< orphan*/  ufshcd_toggle_vreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ufshcd_vreg_set_lpm(struct ufs_hba *hba)
{
	/*
	 * It seems some UFS devices may keep drawing more than sleep current
	 * (atleast for 500us) from UFS rails (especially from VCCQ rail).
	 * To avoid this situation, add 2ms delay before putting these UFS
	 * rails in LPM mode.
	 */
	if (!ufshcd_is_link_active(hba) &&
	    hba->dev_quirks & UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM)
		usleep_range(2000, 2100);

	/*
	 * If UFS device is either in UFS_Sleep turn off VCC rail to save some
	 * power.
	 *
	 * If UFS device and link is in OFF state, all power supplies (VCC,
	 * VCCQ, VCCQ2) can be turned off if power on write protect is not
	 * required. If UFS link is inactive (Hibern8 or OFF state) and device
	 * is in sleep state, put VCCQ & VCCQ2 rails in LPM mode.
	 *
	 * Ignore the error returned by ufshcd_toggle_vreg() as device is anyway
	 * in low power state which would save some power.
	 */
	if (ufshcd_is_ufs_dev_poweroff(hba) && ufshcd_is_link_off(hba) &&
	    !hba->dev_info.is_lu_power_on_wp) {
		ufshcd_setup_vreg(hba, false);
	} else if (!ufshcd_is_ufs_dev_active(hba)) {
		ufshcd_toggle_vreg(hba->dev, hba->vreg_info.vcc, false);
		if (!ufshcd_is_link_active(hba)) {
			ufshcd_config_vreg_lpm(hba, hba->vreg_info.vccq);
			ufshcd_config_vreg_lpm(hba, hba->vreg_info.vccq2);
		}
	}
}