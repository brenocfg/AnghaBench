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

/* Variables and functions */
 int NL80211_RRF_AUTO_BW ; 
 int NL80211_RRF_DFS ; 
 int NL80211_RRF_IR_CONCURRENT ; 
 int NL80211_RRF_NO_160MHZ ; 
 int NL80211_RRF_NO_80MHZ ; 
 int NL80211_RRF_NO_CCK ; 
 int NL80211_RRF_NO_HT40MINUS ; 
 int NL80211_RRF_NO_HT40PLUS ; 
 int NL80211_RRF_NO_INDOOR ; 
 int NL80211_RRF_NO_IR ; 
 int NL80211_RRF_NO_OFDM ; 
 int NL80211_RRF_NO_OUTDOOR ; 
 int NL80211_RRF_PTMP_ONLY ; 
 int NL80211_RRF_PTP_ONLY ; 
 int QLINK_RRF_AUTO_BW ; 
 int QLINK_RRF_DFS ; 
 int QLINK_RRF_IR_CONCURRENT ; 
 int QLINK_RRF_NO_160MHZ ; 
 int QLINK_RRF_NO_80MHZ ; 
 int QLINK_RRF_NO_CCK ; 
 int QLINK_RRF_NO_HT40MINUS ; 
 int QLINK_RRF_NO_HT40PLUS ; 
 int QLINK_RRF_NO_INDOOR ; 
 int QLINK_RRF_NO_IR ; 
 int QLINK_RRF_NO_OFDM ; 
 int QLINK_RRF_NO_OUTDOOR ; 
 int QLINK_RRF_PTMP_ONLY ; 
 int QLINK_RRF_PTP_ONLY ; 

__attribute__((used)) static u32 qtnf_cmd_resp_reg_rule_flags_parse(u32 qflags)
{
	u32 flags = 0;

	if (qflags & QLINK_RRF_NO_OFDM)
		flags |= NL80211_RRF_NO_OFDM;

	if (qflags & QLINK_RRF_NO_CCK)
		flags |= NL80211_RRF_NO_CCK;

	if (qflags & QLINK_RRF_NO_INDOOR)
		flags |= NL80211_RRF_NO_INDOOR;

	if (qflags & QLINK_RRF_NO_OUTDOOR)
		flags |= NL80211_RRF_NO_OUTDOOR;

	if (qflags & QLINK_RRF_DFS)
		flags |= NL80211_RRF_DFS;

	if (qflags & QLINK_RRF_PTP_ONLY)
		flags |= NL80211_RRF_PTP_ONLY;

	if (qflags & QLINK_RRF_PTMP_ONLY)
		flags |= NL80211_RRF_PTMP_ONLY;

	if (qflags & QLINK_RRF_NO_IR)
		flags |= NL80211_RRF_NO_IR;

	if (qflags & QLINK_RRF_AUTO_BW)
		flags |= NL80211_RRF_AUTO_BW;

	if (qflags & QLINK_RRF_IR_CONCURRENT)
		flags |= NL80211_RRF_IR_CONCURRENT;

	if (qflags & QLINK_RRF_NO_HT40MINUS)
		flags |= NL80211_RRF_NO_HT40MINUS;

	if (qflags & QLINK_RRF_NO_HT40PLUS)
		flags |= NL80211_RRF_NO_HT40PLUS;

	if (qflags & QLINK_RRF_NO_80MHZ)
		flags |= NL80211_RRF_NO_80MHZ;

	if (qflags & QLINK_RRF_NO_160MHZ)
		flags |= NL80211_RRF_NO_160MHZ;

	return flags;
}