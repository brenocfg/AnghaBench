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
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_2__ phydm; } ;
struct rtl_efuse {int crystalcap; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int (* phydm_phy_bb_config ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AFE_PLL_CTRL_8822B ; 
 int /*<<< orphan*/  REG_AFE_XTAL_CTRL_8822B ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (struct rtl_priv*) ; 

bool rtl8822be_phy_bb_config(struct ieee80211_hw *hw)
{
	bool rtstatus = true;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 crystal_cap;
	/* u32 tmp; */

	rtstatus = rtlpriv->phydm.ops->phydm_phy_bb_config(rtlpriv);

	/* write 0x28[6:1] = 0x24[30:25] = CrystalCap */
	crystal_cap = rtlefuse->crystalcap & 0x3F;
	rtl_set_bbreg(hw, REG_AFE_XTAL_CTRL_8822B, 0x7E000000, crystal_cap);
	rtl_set_bbreg(hw, REG_AFE_PLL_CTRL_8822B, 0x7E, crystal_cap);

	/*rtlphy->reg_837 = rtl_read_byte(rtlpriv, 0x837);*/ /*unused*/

	return rtstatus;
}