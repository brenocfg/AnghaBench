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
struct rtl_phy {int current_chan_bw; int set_bwmode_inprogress; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_mac {int cur_40_prime_sc; } ;
struct rtl_hal {int /*<<< orphan*/  version; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;

/* Variables and functions */
 int BCCK_SIDEBAND ; 
 int BRFMOD ; 
 scalar_t__ BW_OPMODE ; 
 int BW_OPMODE_20MHZ ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_TRACE ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RCCK0_SYSTEM ; 
 scalar_t__ RFPGA0_ANALOGPARAMETER2 ; 
 int /*<<< orphan*/  RFPGA0_RFMOD ; 
 int /*<<< orphan*/  RFPGA1_RFMOD ; 
 int /*<<< orphan*/  ROFDM1_LSTF ; 
 scalar_t__ RRSR ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  VERSION_8192S_BCUT ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl92s_phy_rf6052_set_bandwidth (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 

void rtl92s_phy_set_bw_mode(struct ieee80211_hw *hw,
			    enum nl80211_channel_type ch_type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 reg_bw_opmode;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "Switch to %s bandwidth\n",
		 rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		 "20MHz" : "40MHz");

	if (rtlphy->set_bwmode_inprogress)
		return;
	if (is_hal_stop(rtlhal))
		return;

	rtlphy->set_bwmode_inprogress = true;

	reg_bw_opmode = rtl_read_byte(rtlpriv, BW_OPMODE);
	/* dummy read */
	rtl_read_byte(rtlpriv, RRSR + 2);

	switch (rtlphy->current_chan_bw) {
	case HT_CHANNEL_WIDTH_20:
		reg_bw_opmode |= BW_OPMODE_20MHZ;
		rtl_write_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);
		break;
	case HT_CHANNEL_WIDTH_20_40:
		reg_bw_opmode &= ~BW_OPMODE_20MHZ;
		rtl_write_byte(rtlpriv, BW_OPMODE, reg_bw_opmode);
		break;
	default:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		break;
	}

	switch (rtlphy->current_chan_bw) {
	case HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x0);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x0);

		if (rtlhal->version >= VERSION_8192S_BCUT)
			rtl_write_byte(rtlpriv, RFPGA0_ANALOGPARAMETER2, 0x58);
		break;
	case HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);

		rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCK_SIDEBAND,
				(mac->cur_40_prime_sc >> 1));
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00, mac->cur_40_prime_sc);

		if (rtlhal->version >= VERSION_8192S_BCUT)
			rtl_write_byte(rtlpriv, RFPGA0_ANALOGPARAMETER2, 0x18);
		break;
	default:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		break;
	}

	rtl92s_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");
}