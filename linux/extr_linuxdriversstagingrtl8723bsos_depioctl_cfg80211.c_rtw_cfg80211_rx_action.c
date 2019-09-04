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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*,int) ; 
 int /*<<< orphan*/  DBG_871X (char*,char const*,...) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  rtw_action_frame_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_cfg80211_rx_mgmt (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtw_get_oper_ch (struct adapter*) ; 
 int /*<<< orphan*/  rtw_ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 

void rtw_cfg80211_rx_action(struct adapter *adapter, u8 *frame, uint frame_len, const char*msg)
{
	s32 freq;
	int channel;
	u8 category, action;

	channel = rtw_get_oper_ch(adapter);

	rtw_action_frame_parse(frame, frame_len, &category, &action);

	DBG_8192C("RTW_Rx:cur_ch =%d\n", channel);
	if (msg)
		DBG_871X("RTW_Rx:%s\n", msg);
	else
		DBG_871X("RTW_Rx:category(%u), action(%u)\n", category, action);

	freq = rtw_ieee80211_channel_to_frequency(channel, NL80211_BAND_2GHZ);

	rtw_cfg80211_rx_mgmt(adapter, freq, 0, frame, frame_len, GFP_ATOMIC);
}