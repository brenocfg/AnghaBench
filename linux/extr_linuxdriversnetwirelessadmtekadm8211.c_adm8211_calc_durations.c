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

/* Variables and functions */
 int PLCP_SIGNAL_11M ; 
 int PLCP_SIGNAL_2M ; 

__attribute__((used)) static void adm8211_calc_durations(int *dur, int *plcp, size_t payload_len, int len,
				   int plcp_signal, int short_preamble)
{
	/* Alternative calculation from NetBSD: */

/* IEEE 802.11b durations for DSSS PHY in microseconds */
#define IEEE80211_DUR_DS_LONG_PREAMBLE	144
#define IEEE80211_DUR_DS_SHORT_PREAMBLE	72
#define IEEE80211_DUR_DS_FAST_PLCPHDR	24
#define IEEE80211_DUR_DS_SLOW_PLCPHDR	48
#define IEEE80211_DUR_DS_SLOW_ACK	112
#define IEEE80211_DUR_DS_FAST_ACK	56
#define IEEE80211_DUR_DS_SLOW_CTS	112
#define IEEE80211_DUR_DS_FAST_CTS	56
#define IEEE80211_DUR_DS_SLOT		20
#define IEEE80211_DUR_DS_SIFS		10

	int remainder;

	*dur = (80 * (24 + payload_len) + plcp_signal - 1)
		/ plcp_signal;

	if (plcp_signal <= PLCP_SIGNAL_2M)
		/* 1-2Mbps WLAN: send ACK/CTS at 1Mbps */
		*dur += 3 * (IEEE80211_DUR_DS_SIFS +
			     IEEE80211_DUR_DS_SHORT_PREAMBLE +
			     IEEE80211_DUR_DS_FAST_PLCPHDR) +
			     IEEE80211_DUR_DS_SLOW_CTS + IEEE80211_DUR_DS_SLOW_ACK;
	else
		/* 5-11Mbps WLAN: send ACK/CTS at 2Mbps */
		*dur += 3 * (IEEE80211_DUR_DS_SIFS +
			     IEEE80211_DUR_DS_SHORT_PREAMBLE +
			     IEEE80211_DUR_DS_FAST_PLCPHDR) +
			     IEEE80211_DUR_DS_FAST_CTS + IEEE80211_DUR_DS_FAST_ACK;

	/* lengthen duration if long preamble */
	if (!short_preamble)
		*dur +=	3 * (IEEE80211_DUR_DS_LONG_PREAMBLE -
			     IEEE80211_DUR_DS_SHORT_PREAMBLE) +
			3 * (IEEE80211_DUR_DS_SLOW_PLCPHDR -
			     IEEE80211_DUR_DS_FAST_PLCPHDR);


	*plcp = (80 * len) / plcp_signal;
	remainder = (80 * len) % plcp_signal;
	if (plcp_signal == PLCP_SIGNAL_11M &&
	    remainder <= 30 && remainder > 0)
		*plcp = (*plcp | 0x8000) + 1;
	else if (remainder)
		(*plcp)++;
}