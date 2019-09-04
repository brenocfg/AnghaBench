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
 int IEEE80211_CHAN_INDOOR_ONLY ; 
 int IEEE80211_CHAN_IR_CONCURRENT ; 
 int IEEE80211_CHAN_NO_160MHZ ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_NO_OFDM ; 
 int IEEE80211_CHAN_RADAR ; 
 int NL80211_RRF_DFS ; 
 int NL80211_RRF_IR_CONCURRENT ; 
 int NL80211_RRF_NO_160MHZ ; 
 int NL80211_RRF_NO_80MHZ ; 
 int NL80211_RRF_NO_HT40MINUS ; 
 int NL80211_RRF_NO_HT40PLUS ; 
 int NL80211_RRF_NO_IR_ALL ; 
 int NL80211_RRF_NO_OFDM ; 
 int NL80211_RRF_NO_OUTDOOR ; 

__attribute__((used)) static u32 map_regdom_flags(u32 rd_flags)
{
	u32 channel_flags = 0;
	if (rd_flags & NL80211_RRF_NO_IR_ALL)
		channel_flags |= IEEE80211_CHAN_NO_IR;
	if (rd_flags & NL80211_RRF_DFS)
		channel_flags |= IEEE80211_CHAN_RADAR;
	if (rd_flags & NL80211_RRF_NO_OFDM)
		channel_flags |= IEEE80211_CHAN_NO_OFDM;
	if (rd_flags & NL80211_RRF_NO_OUTDOOR)
		channel_flags |= IEEE80211_CHAN_INDOOR_ONLY;
	if (rd_flags & NL80211_RRF_IR_CONCURRENT)
		channel_flags |= IEEE80211_CHAN_IR_CONCURRENT;
	if (rd_flags & NL80211_RRF_NO_HT40MINUS)
		channel_flags |= IEEE80211_CHAN_NO_HT40MINUS;
	if (rd_flags & NL80211_RRF_NO_HT40PLUS)
		channel_flags |= IEEE80211_CHAN_NO_HT40PLUS;
	if (rd_flags & NL80211_RRF_NO_80MHZ)
		channel_flags |= IEEE80211_CHAN_NO_80MHZ;
	if (rd_flags & NL80211_RRF_NO_160MHZ)
		channel_flags |= IEEE80211_CHAN_NO_160MHZ;
	return channel_flags;
}