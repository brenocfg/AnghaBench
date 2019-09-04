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
typedef  int u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASEBAND_CONFIG_PHY_REG ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int* RTL8188EEPHY_REG_ARRAY_PG ; 
 int RTL8188EEPHY_REG_ARRAY_PGLEN ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl88e_check_condition (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  store_pwrindex_rate_offset (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool phy_config_bb_with_pghdr(struct ieee80211_hw *hw, u8 configtype)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int i;
	u32 *phy_reg_page;
	u16 phy_reg_page_len;
	u32 v1 = 0, v2 = 0, v3 = 0;

	phy_reg_page_len = RTL8188EEPHY_REG_ARRAY_PGLEN;
	phy_reg_page = RTL8188EEPHY_REG_ARRAY_PG;

	if (configtype == BASEBAND_CONFIG_PHY_REG) {
		for (i = 0; i < phy_reg_page_len; i = i + 3) {
			v1 = phy_reg_page[i];
			v2 = phy_reg_page[i+1];
			v3 = phy_reg_page[i+2];

			if (v1 < 0xcdcdcdcd) {
				if (phy_reg_page[i] == 0xfe)
					mdelay(50);
				else if (phy_reg_page[i] == 0xfd)
					mdelay(5);
				else if (phy_reg_page[i] == 0xfc)
					mdelay(1);
				else if (phy_reg_page[i] == 0xfb)
					udelay(50);
				else if (phy_reg_page[i] == 0xfa)
					udelay(5);
				else if (phy_reg_page[i] == 0xf9)
					udelay(1);

				store_pwrindex_rate_offset(hw, phy_reg_page[i],
							   phy_reg_page[i + 1],
							   phy_reg_page[i + 2]);
				continue;
			} else {
				if (!_rtl88e_check_condition(hw,
							     phy_reg_page[i])) {
					/*don't need the hw_body*/
				    i += 2; /* skip the pair of expression*/
				    /* to protect 'i+1' 'i+2' not overrun */
				    if (i >= phy_reg_page_len - 2)
					break;

				    v1 = phy_reg_page[i];
				    v2 = phy_reg_page[i+1];
				    v3 = phy_reg_page[i+2];
				    while (v2 != 0xDEAD &&
					   i < phy_reg_page_len - 5) {
					i += 3;
					v1 = phy_reg_page[i];
					v2 = phy_reg_page[i+1];
					v3 = phy_reg_page[i+2];
				    }
				}
			}
		}
	} else {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "configtype != BaseBand_Config_PHY_REG\n");
	}
	return true;
}