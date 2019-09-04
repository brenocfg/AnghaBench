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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_phy {struct bb_reg_def* phyreg_def; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct bb_reg_def {int /*<<< orphan*/  rfintfs; } ;

/* Variables and functions */
 int BRFSI_RFENV ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl92d_phy_restore_rf_env(struct ieee80211_hw *hw, u8 rfpath,
				       u32 *pu4_regval)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];

	RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD, "=====>\n");
	/*----Restore RFENV control type----*/
	switch (rfpath) {
	case RF90_PATH_A:
	case RF90_PATH_C:
		rtl_set_bbreg(hw, pphyreg->rfintfs, BRFSI_RFENV, *pu4_regval);
		break;
	case RF90_PATH_B:
	case RF90_PATH_D:
		rtl_set_bbreg(hw, pphyreg->rfintfs, BRFSI_RFENV << 16,
			      *pu4_regval);
		break;
	}
	RT_TRACE(rtlpriv, COMP_RF, DBG_LOUD, "<=====\n");
}