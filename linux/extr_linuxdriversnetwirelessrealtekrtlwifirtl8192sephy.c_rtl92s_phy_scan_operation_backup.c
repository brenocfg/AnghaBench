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
typedef  int u8 ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CMD_PAUSE_DM_BY_SCAN ; 
 int /*<<< orphan*/  FW_CMD_RESUME_DM_BY_SCAN ; 
#define  SCAN_OPT_BACKUP 129 
#define  SCAN_OPT_RESTORE 128 
 int /*<<< orphan*/  is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl92s_phy_set_fw_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

void rtl92s_phy_scan_operation_backup(struct ieee80211_hw *hw,
				      u8 operation)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (!is_hal_stop(rtlhal)) {
		switch (operation) {
		case SCAN_OPT_BACKUP:
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_PAUSE_DM_BY_SCAN);
			break;
		case SCAN_OPT_RESTORE:
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_RESUME_DM_BY_SCAN);
			break;
		default:
			pr_err("Unknown operation\n");
			break;
		}
	}
}