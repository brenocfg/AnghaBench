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
struct rtl_phy {void* reg_837; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct rtl_efuse {int crystalcap; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int FEN_BBRSTB ; 
 int FEN_BB_GLB_RSTN ; 
 int FEN_PCIEA ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL ; 
 int REG_OPT_CTRL ; 
 int REG_RF_CTRL ; 
 int REG_SYS_FUNC_EN ; 
 int _rtl8821ae_phy_bb8821a_config_parafile (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  phy_init_bb_rf_register_definition (struct ieee80211_hw*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 void* rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

bool rtl8821ae_phy_bb_config(struct ieee80211_hw *hw)
{
	bool rtstatus = true;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 regval;
	u8 crystal_cap;

	phy_init_bb_rf_register_definition(hw);

	regval = rtl_read_byte(rtlpriv, REG_SYS_FUNC_EN);
	regval |= FEN_PCIEA;
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, regval);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN,
		       regval | FEN_BB_GLB_RSTN | FEN_BBRSTB);

	rtl_write_byte(rtlpriv, REG_RF_CTRL, 0x7);
	rtl_write_byte(rtlpriv, REG_OPT_CTRL + 2, 0x7);

	rtstatus = _rtl8821ae_phy_bb8821a_config_parafile(hw);

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
		crystal_cap = rtlefuse->crystalcap & 0x3F;
		rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0x7FF80000,
			      (crystal_cap | (crystal_cap << 6)));
	} else {
		crystal_cap = rtlefuse->crystalcap & 0x3F;
		rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
			      (crystal_cap | (crystal_cap << 6)));
	}
	rtlphy->reg_837 = rtl_read_byte(rtlpriv, 0x837);

	return rtstatus;
}