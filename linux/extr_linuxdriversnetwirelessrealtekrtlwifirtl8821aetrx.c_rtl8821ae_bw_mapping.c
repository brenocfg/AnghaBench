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
struct rtl_tcb_desc {scalar_t__ packet_bw; } ;
struct rtl_phy {scalar_t__ current_chan_bw; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ HT_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 rtl8821ae_bw_mapping(struct ieee80211_hw *hw,
			       struct rtl_tcb_desc *ptcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 bw_setting_of_desc = 0;

	RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
		 "rtl8821ae_bw_mapping, current_chan_bw %d, packet_bw %d\n",
		 rtlphy->current_chan_bw, ptcb_desc->packet_bw);

	if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) {
		if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_80)
			bw_setting_of_desc = 2;
		else if (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40)
			bw_setting_of_desc = 1;
		else
			bw_setting_of_desc = 0;
	} else if (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) {
		if ((ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) ||
		    (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_80))
			bw_setting_of_desc = 1;
		else
			bw_setting_of_desc = 0;
	} else {
		bw_setting_of_desc = 0;
	}
	return bw_setting_of_desc;
}