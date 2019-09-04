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
struct rtl_phy {int rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {scalar_t__ hw_type; int hw_rof_enable; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8821ae { ____Placeholder_version_8821ae } version_8821ae ;

/* Variables and functions */
 int CHIP_8812 ; 
 int CHIP_8821 ; 
 int CHIP_VER_RTL_MASK ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ HARDWARE_TYPE_RTL8812AE ; 
 scalar_t__ HARDWARE_TYPE_RTL8821AE ; 
 int NORMAL_CHIP ; 
 int /*<<< orphan*/  REG_MULTI_FUNC_CTRL ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 int RF_1T1R ; 
 scalar_t__ RF_2T2R ; 
 int RF_TYPE_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int TRP_VAUX_EN ; 
#define  VERSION_NORMAL_TSMC_CHIP_1T1R_8812 136 
#define  VERSION_NORMAL_TSMC_CHIP_1T1R_8812_C_CUT 135 
#define  VERSION_NORMAL_TSMC_CHIP_2T2R_8812 134 
#define  VERSION_NORMAL_TSMC_CHIP_2T2R_8812_C_CUT 133 
#define  VERSION_NORMAL_TSMC_CHIP_8821 132 
#define  VERSION_NORMAL_TSMC_CHIP_8821_B_CUT 131 
#define  VERSION_TEST_CHIP_1T1R_8812 130 
#define  VERSION_TEST_CHIP_2T2R_8812 129 
#define  VERSION_TEST_CHIP_8821 128 
 int VERSION_UNKNOWN ; 
 int WL_HWROF_EN ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum version_8821ae _rtl8821ae_read_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	enum version_8821ae version = VERSION_UNKNOWN;
	u32 value32;

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "ReadChipVersion8812A 0xF0 = 0x%x\n", value32);

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
		rtlphy->rf_type = RF_2T2R;
	else if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE)
		rtlphy->rf_type = RF_1T1R;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "RF_Type is %x!!\n", rtlphy->rf_type);

	if (value32 & TRP_VAUX_EN) {
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			if (rtlphy->rf_type == RF_2T2R)
				version = VERSION_TEST_CHIP_2T2R_8812;
			else
				version = VERSION_TEST_CHIP_1T1R_8812;
		} else
			version = VERSION_TEST_CHIP_8821;
	} else {
		if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) {
			u32 rtl_id = ((value32 & CHIP_VER_RTL_MASK) >> 12) + 1;

			if (rtlphy->rf_type == RF_2T2R)
				version =
					(enum version_8821ae)(CHIP_8812
					| NORMAL_CHIP |
					RF_TYPE_2T2R);
			else
				version = (enum version_8821ae)(CHIP_8812
					| NORMAL_CHIP);

			version = (enum version_8821ae)(version | (rtl_id << 12));
		} else if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
			u32 rtl_id = value32 & CHIP_VER_RTL_MASK;

			version = (enum version_8821ae)(CHIP_8821
				| NORMAL_CHIP | rtl_id);
		}
	}

	if (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) {
		/*WL_HWROF_EN.*/
		value32 = rtl_read_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		rtlhal->hw_rof_enable = ((value32 & WL_HWROF_EN) ? 1 : 0);
	}

	switch (version) {
	case VERSION_TEST_CHIP_1T1R_8812:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_TEST_CHIP_1T1R_8812\n");
		break;
	case VERSION_TEST_CHIP_2T2R_8812:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_TEST_CHIP_2T2R_8812\n");
		break;
	case VERSION_NORMAL_TSMC_CHIP_1T1R_8812:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID:VERSION_NORMAL_TSMC_CHIP_1T1R_8812\n");
		break;
	case VERSION_NORMAL_TSMC_CHIP_2T2R_8812:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_NORMAL_TSMC_CHIP_2T2R_8812\n");
		break;
	case VERSION_NORMAL_TSMC_CHIP_1T1R_8812_C_CUT:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_NORMAL_TSMC_CHIP_1T1R_8812 C CUT\n");
		break;
	case VERSION_NORMAL_TSMC_CHIP_2T2R_8812_C_CUT:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_NORMAL_TSMC_CHIP_2T2R_8812 C CUT\n");
		break;
	case VERSION_TEST_CHIP_8821:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_TEST_CHIP_8821\n");
		break;
	case VERSION_NORMAL_TSMC_CHIP_8821:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_NORMAL_TSMC_CHIP_8821 A CUT\n");
		break;
	case VERSION_NORMAL_TSMC_CHIP_8821_B_CUT:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: VERSION_NORMAL_TSMC_CHIP_8821 B CUT\n");
		break;
	default:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Chip Version ID: Unknown (0x%X)\n", version);
		break;
	}

	return version;
}