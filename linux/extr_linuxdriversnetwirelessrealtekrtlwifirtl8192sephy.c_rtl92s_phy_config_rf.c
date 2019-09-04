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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  MASK20BITS ; 
 int RADIOA_1T_ARRAYLENGTH ; 
 int RADIOB_ARRAYLENGTH ; 
 int RADIOB_GM_ARRAYLENGTH ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 scalar_t__ RF_2T2R_GREEN ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _rtl92s_phy_config_rfpa_bias_current (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/ * rtl8192seradioa_1t_array ; 
 int /*<<< orphan*/ * rtl8192seradiob_array ; 
 int /*<<< orphan*/ * rtl8192seradiob_gm_array ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_rfreg_delay (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 rtl92s_phy_config_rf(struct ieee80211_hw *hw, enum radio_path rfpath)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	int i;
	bool rtstatus = true;
	u32 *radio_a_table;
	u32 *radio_b_table;
	u16 radio_a_tblen, radio_b_tblen;

	radio_a_tblen = RADIOA_1T_ARRAYLENGTH;
	radio_a_table = rtl8192seradioa_1t_array;

	/* Using Green mode array table for RF_2T2R_GREEN */
	if (rtlphy->rf_type == RF_2T2R_GREEN) {
		radio_b_table = rtl8192seradiob_gm_array;
		radio_b_tblen = RADIOB_GM_ARRAYLENGTH;
	} else {
		radio_b_table = rtl8192seradiob_array;
		radio_b_tblen = RADIOB_ARRAYLENGTH;
	}

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	rtstatus = true;

	switch (rfpath) {
	case RF90_PATH_A:
		for (i = 0; i < radio_a_tblen; i = i + 2) {
			rtl_rfreg_delay(hw, rfpath, radio_a_table[i],
					MASK20BITS, radio_a_table[i + 1]);

		}

		/* PA Bias current for inferiority IC */
		_rtl92s_phy_config_rfpa_bias_current(hw, rfpath);
		break;
	case RF90_PATH_B:
		for (i = 0; i < radio_b_tblen; i = i + 2) {
			rtl_rfreg_delay(hw, rfpath, radio_b_table[i],
					MASK20BITS, radio_b_table[i + 1]);
		}
		break;
	case RF90_PATH_C:
		;
		break;
	case RF90_PATH_D:
		;
		break;
	default:
		break;
	}

	return rtstatus;
}