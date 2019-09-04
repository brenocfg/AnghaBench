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
typedef  int u16 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int AGCTAB_ARRAYLENGTH ; 
 scalar_t__ BASEBAND_CONFIG_AGC_TAB ; 
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int PHY_REG_2T2RARRAYLENGTH ; 
 int /*<<< orphan*/ * rtl8192seagctab_array ; 
 int /*<<< orphan*/ * rtl8192sephy_reg_2t2rarray ; 
 int /*<<< orphan*/  rtl92s_phy_set_bb_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_addr_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool _rtl92s_phy_config_bb(struct ieee80211_hw *hw, u8 configtype)
{
	int i;
	u32 *phy_reg_table;
	u32 *agc_table;
	u16 phy_reg_len, agc_len;

	agc_len = AGCTAB_ARRAYLENGTH;
	agc_table = rtl8192seagctab_array;
	/* Default RF_type: 2T2R */
	phy_reg_len = PHY_REG_2T2RARRAYLENGTH;
	phy_reg_table = rtl8192sephy_reg_2t2rarray;

	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		for (i = 0; i < phy_reg_len; i = i + 2) {
			rtl_addr_delay(phy_reg_table[i]);

			/* Add delay for ECS T20 & LG malow platform, */
			udelay(1);

			rtl92s_phy_set_bb_reg(hw, phy_reg_table[i], MASKDWORD,
					phy_reg_table[i + 1]);
		}
	} else if (configtype == BASEBAND_CONFIG_AGC_TAB) {
		for (i = 0; i < agc_len; i = i + 2) {
			rtl92s_phy_set_bb_reg(hw, agc_table[i], MASKDWORD,
					agc_table[i + 1]);

			/* Add delay for ECS T20 & LG malow platform */
			udelay(1);
		}
	}

	return true;
}