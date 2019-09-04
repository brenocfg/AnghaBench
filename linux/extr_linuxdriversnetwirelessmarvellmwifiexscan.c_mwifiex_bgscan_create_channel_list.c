#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct mwifiex_private {TYPE_2__ wdev; struct mwifiex_adapter* adapter; } ;
struct mwifiex_chan_scan_param_set {int radio_type; scalar_t__ chan_number; int /*<<< orphan*/  chan_scan_mode_bitmap; void* max_scan_time; } ;
struct mwifiex_bg_scan_cfg {TYPE_3__* chan_list; } ;
struct mwifiex_adapter {int /*<<< orphan*/  specific_scan_time; int /*<<< orphan*/  passive_scan_time; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_channel {int flags; scalar_t__ hw_value; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_6__ {scalar_t__ scan_time; } ;
struct TYPE_4__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_IR ; 
 int /*<<< orphan*/  MWIFIEX_PASSIVE_SCAN ; 
 int NUM_NL80211_BANDS ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_bgscan_create_channel_list(struct mwifiex_private *priv,
				   const struct mwifiex_bg_scan_cfg
						*bgscan_cfg_in,
				   struct mwifiex_chan_scan_param_set
						*scan_chan_list)
{
	enum nl80211_band band;
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *ch;
	struct mwifiex_adapter *adapter = priv->adapter;
	int chan_idx = 0, i;

	for (band = 0; (band < NUM_NL80211_BANDS); band++) {
		if (!priv->wdev.wiphy->bands[band])
			continue;

		sband = priv->wdev.wiphy->bands[band];

		for (i = 0; (i < sband->n_channels) ; i++) {
			ch = &sband->channels[i];
			if (ch->flags & IEEE80211_CHAN_DISABLED)
				continue;
			scan_chan_list[chan_idx].radio_type = band;

			if (bgscan_cfg_in->chan_list[0].scan_time)
				scan_chan_list[chan_idx].max_scan_time =
					cpu_to_le16((u16)bgscan_cfg_in->
					chan_list[0].scan_time);
			else if (ch->flags & IEEE80211_CHAN_NO_IR)
				scan_chan_list[chan_idx].max_scan_time =
					cpu_to_le16(adapter->passive_scan_time);
			else
				scan_chan_list[chan_idx].max_scan_time =
					cpu_to_le16(adapter->
						    specific_scan_time);

			if (ch->flags & IEEE80211_CHAN_NO_IR)
				scan_chan_list[chan_idx].chan_scan_mode_bitmap
					|= MWIFIEX_PASSIVE_SCAN;
			else
				scan_chan_list[chan_idx].chan_scan_mode_bitmap
					&= ~MWIFIEX_PASSIVE_SCAN;

			scan_chan_list[chan_idx].chan_number =
							(u32)ch->hw_value;
			chan_idx++;
		}
	}
	return chan_idx;
}