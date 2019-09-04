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
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;

/* Variables and functions */
 int NL80211_CHAN_WIDTH_10 ; 
 int NL80211_CHAN_WIDTH_160 ; 
 int NL80211_CHAN_WIDTH_20 ; 
 int NL80211_CHAN_WIDTH_20_NOHT ; 
 int NL80211_CHAN_WIDTH_40 ; 
 int NL80211_CHAN_WIDTH_5 ; 
 int NL80211_CHAN_WIDTH_80 ; 
 int NL80211_CHAN_WIDTH_80P80 ; 
#define  QLINK_CHAN_WIDTH_10 135 
#define  QLINK_CHAN_WIDTH_160 134 
#define  QLINK_CHAN_WIDTH_20 133 
#define  QLINK_CHAN_WIDTH_20_NOHT 132 
#define  QLINK_CHAN_WIDTH_40 131 
#define  QLINK_CHAN_WIDTH_5 130 
#define  QLINK_CHAN_WIDTH_80 129 
#define  QLINK_CHAN_WIDTH_80P80 128 

__attribute__((used)) static enum nl80211_chan_width qlink_chanwidth_to_nl(u8 qlw)
{
	switch (qlw) {
	case QLINK_CHAN_WIDTH_20_NOHT:
		return NL80211_CHAN_WIDTH_20_NOHT;
	case QLINK_CHAN_WIDTH_20:
		return NL80211_CHAN_WIDTH_20;
	case QLINK_CHAN_WIDTH_40:
		return NL80211_CHAN_WIDTH_40;
	case QLINK_CHAN_WIDTH_80:
		return NL80211_CHAN_WIDTH_80;
	case QLINK_CHAN_WIDTH_80P80:
		return NL80211_CHAN_WIDTH_80P80;
	case QLINK_CHAN_WIDTH_160:
		return NL80211_CHAN_WIDTH_160;
	case QLINK_CHAN_WIDTH_5:
		return NL80211_CHAN_WIDTH_5;
	case QLINK_CHAN_WIDTH_10:
		return NL80211_CHAN_WIDTH_10;
	default:
		return -1;
	}
}