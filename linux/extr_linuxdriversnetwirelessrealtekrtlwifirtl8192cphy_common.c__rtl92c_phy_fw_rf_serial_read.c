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
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

u32 _rtl92c_phy_fw_rf_serial_read(struct ieee80211_hw *hw,
				  enum radio_path rfpath, u32 offset)
{
	WARN_ONCE(true, "rtl8192c-common: _rtl92c_phy_fw_rf_serial_read deprecated!\n");
	return 0;
}