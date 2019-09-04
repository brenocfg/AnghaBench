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
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  RFREG_OFFSET_MASK ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl8821ae_config_rf_reg(struct ieee80211_hw *hw,
				     u32 addr, u32 data,
				     enum radio_path rfpath, u32 regaddr)
{
	if (addr == 0xfe || addr == 0xffe) {
		/* In order not to disturb BT music when
		 * wifi init.(1ant NIC only)
		 */
		mdelay(50);
	} else {
		rtl_set_rfreg(hw, rfpath, regaddr, RFREG_OFFSET_MASK, data);
		udelay(1);
	}
}