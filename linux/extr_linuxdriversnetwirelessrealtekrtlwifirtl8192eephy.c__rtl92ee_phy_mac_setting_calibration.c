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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 

__attribute__((used)) static void _rtl92ee_phy_mac_setting_calibration(struct ieee80211_hw *hw,
						 u32 *macreg, u32 *macbackup)
{
	rtl_set_bbreg(hw, 0x520, 0x00ff0000, 0xff);
}