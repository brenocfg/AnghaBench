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
typedef  int u32 ;
struct rtl_phy {size_t num_total_rfpath; struct bb_reg_def* phyreg_def; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
struct bb_reg_def {int /*<<< orphan*/  rfintfs; int /*<<< orphan*/  rfhssi_para2; int /*<<< orphan*/  rfintfo; int /*<<< orphan*/  rfintfe; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int B3WIRE_ADDRESSLENGTH ; 
 int B3WIRE_DATALENGTH ; 
 int BRFSI_RFENV ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int rtl92s_phy_config_rf (struct ieee80211_hw*,int) ; 
 int rtl92s_phy_query_bb_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92s_phy_set_bb_reg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl92s_phy_rf6052_config(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 u4reg_val = 0;
	u8 rfpath;
	bool rtstatus = true;
	struct bb_reg_def *pphyreg;

	/* Initialize RF */
	for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {

		pphyreg = &rtlphy->phyreg_def[rfpath];

		/* Store original RFENV control type */
		switch (rfpath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			u4reg_val = rtl92s_phy_query_bb_reg(hw,
							    pphyreg->rfintfs,
							    BRFSI_RFENV);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			u4reg_val = rtl92s_phy_query_bb_reg(hw,
							    pphyreg->rfintfs,
							    BRFSI_RFENV << 16);
			break;
		}

		/* Set RF_ENV enable */
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfintfe,
				      BRFSI_RFENV << 16, 0x1);

		/* Set RF_ENV output high */
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfintfo, BRFSI_RFENV, 0x1);

		/* Set bit number of Address and Data for RF register */
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfhssi_para2,
				B3WIRE_ADDRESSLENGTH, 0x0);
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfhssi_para2,
				B3WIRE_DATALENGTH, 0x0);

		/* Initialize RF fom connfiguration file */
		switch (rfpath) {
		case RF90_PATH_A:
			rtstatus = rtl92s_phy_config_rf(hw,
						(enum radio_path)rfpath);
			break;
		case RF90_PATH_B:
			rtstatus = rtl92s_phy_config_rf(hw,
						(enum radio_path)rfpath);
			break;
		case RF90_PATH_C:
			break;
		case RF90_PATH_D:
			break;
		}

		/* Restore RFENV control type */
		switch (rfpath) {
		case RF90_PATH_A:
		case RF90_PATH_C:
			rtl92s_phy_set_bb_reg(hw, pphyreg->rfintfs, BRFSI_RFENV,
					      u4reg_val);
			break;
		case RF90_PATH_B:
		case RF90_PATH_D:
			rtl92s_phy_set_bb_reg(hw, pphyreg->rfintfs,
					      BRFSI_RFENV << 16,
					      u4reg_val);
			break;
		}

		if (!rtstatus) {
			pr_err("Radio[%d] Fail!!\n", rfpath);
			goto fail;
		}

	}

	return rtstatus;

fail:
	return rtstatus;
}