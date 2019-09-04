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
struct rtl_priv {int dummy; } ;
struct rtl_hal {int dummy; } ;
struct rtl_efuse {scalar_t__ antenna_div_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int MASKLWORD ; 
 int RCONFIG_RAM64x16 ; 
 int /*<<< orphan*/  REG_LEDCFG0 ; 
 int RFPGA0_XAB_RFINTERFACESW ; 
 int RFPGA0_XAB_RFPARAMETER ; 
 int RFPGA0_XA_RFINTERFACEOE ; 
 int RFPGA0_XB_RFINTERFACEOE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92ee_phy_set_rfpath_switch(struct ieee80211_hw *hw,
					   bool bmain, bool is2t)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	RT_TRACE(rtlpriv, COMP_INIT , DBG_LOUD , "\n");

	if (is_hal_stop(rtlhal)) {
		u8 u1btmp;

		u1btmp = rtl_read_byte(rtlpriv, REG_LEDCFG0);
		rtl_write_byte(rtlpriv, REG_LEDCFG0, u1btmp | BIT(7));
		rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(13), 0x01);
	}
	if (is2t) {
		if (bmain)
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(6), 0x1);
		else
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(6), 0x2);
	} else {
		rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, BIT(8) | BIT(9), 0);
		rtl_set_bbreg(hw, 0x914, MASKLWORD, 0x0201);

		/* We use the RF definition of MAIN and AUX,
		 * left antenna and right antenna repectively.
		 * Default output at AUX.
		 */
		if (bmain) {
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE,
				      BIT(14) | BIT(13) | BIT(12), 0);
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(4) | BIT(3), 0);
			if (rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV)
				rtl_set_bbreg(hw, RCONFIG_RAM64x16, BIT(31), 0);
		} else {
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE,
				      BIT(14) | BIT(13) | BIT(12), 1);
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(4) | BIT(3), 1);
			if (rtlefuse->antenna_div_type == CGCS_RX_HW_ANTDIV)
				rtl_set_bbreg(hw, RCONFIG_RAM64x16, BIT(31), 1);
		}
	}
}