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
typedef  int u32 ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int BAND_AAC ; 
 int IEEE80211_VHT_CHANWIDTH_160MHZ ; 
 int IEEE80211_VHT_CHANWIDTH_80MHZ ; 

u8 mwifiex_get_center_freq_index(struct mwifiex_private *priv, u8 band,
				 u32 pri_chan, u8 chan_bw)
{
	u8 center_freq_idx = 0;

	if (band & BAND_AAC) {
		switch (pri_chan) {
		case 36:
		case 40:
		case 44:
		case 48:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 42;
			break;
		case 52:
		case 56:
		case 60:
		case 64:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 58;
			else if (chan_bw == IEEE80211_VHT_CHANWIDTH_160MHZ)
				center_freq_idx = 50;
			break;
		case 100:
		case 104:
		case 108:
		case 112:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 106;
			break;
		case 116:
		case 120:
		case 124:
		case 128:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 122;
			else if (chan_bw == IEEE80211_VHT_CHANWIDTH_160MHZ)
				center_freq_idx = 114;
			break;
		case 132:
		case 136:
		case 140:
		case 144:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 138;
			break;
		case 149:
		case 153:
		case 157:
		case 161:
			if (chan_bw == IEEE80211_VHT_CHANWIDTH_80MHZ)
				center_freq_idx = 155;
			break;
		default:
			center_freq_idx = 42;
		}
	}

	return center_freq_idx;
}