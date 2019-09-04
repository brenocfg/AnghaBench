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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASEBAND_CONFIG_AGC_TAB ; 
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/ * RTL8188EEAGCTAB_1TARRAY ; 
 int /*<<< orphan*/  RTL8188EEAGCTAB_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8188EEPHY_REG_1TARRAY ; 
 int /*<<< orphan*/  RTL8188EEPHY_REG_1TARRAYLEN ; 
 int /*<<< orphan*/  handle_branch1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_branch2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool phy_config_bb_with_headerfile(struct ieee80211_hw *hw,
					  u8 configtype)
{
	u32 *array_table;
	u16 arraylen;

	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		arraylen = RTL8188EEPHY_REG_1TARRAYLEN;
		array_table = RTL8188EEPHY_REG_1TARRAY;
		handle_branch1(hw, arraylen, array_table);
	} else if (configtype == BASEBAND_CONFIG_AGC_TAB) {
		arraylen = RTL8188EEAGCTAB_1TARRAYLEN;
		array_table = RTL8188EEAGCTAB_1TARRAY;
		handle_branch2(hw, arraylen, array_table);
	}
	return true;
}