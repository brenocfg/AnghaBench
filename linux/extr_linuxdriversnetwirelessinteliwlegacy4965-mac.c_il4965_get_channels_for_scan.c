#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct il_scan_channel {int type; int dsp_atten; int tx_gain; void* passive_dwell; void* active_dwell; void* channel; } ;
struct il_priv {TYPE_1__* scan_request; } ;
struct il_channel_info {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_channel {int band; scalar_t__ hw_value; int flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int n_channels; struct ieee80211_channel** channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*,int,...) ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IL_SCAN_PROBE_MASK (scalar_t__) ; 
 int NL80211_BAND_5GHZ ; 
 int SCAN_CHANNEL_TYPE_ACTIVE ; 
 int SCAN_CHANNEL_TYPE_PASSIVE ; 
 void* cpu_to_le16 (scalar_t__) ; 
 scalar_t__ il_get_active_dwell_time (struct il_priv*,int,scalar_t__) ; 
 struct il_channel_info* il_get_channel_info (struct il_priv*,int,scalar_t__) ; 
 struct ieee80211_supported_band* il_get_hw_mode (struct il_priv*,int) ; 
 scalar_t__ il_get_passive_dwell_time (struct il_priv*,int,struct ieee80211_vif*) ; 
 scalar_t__ il_is_channel_passive (struct il_channel_info const*) ; 
 int /*<<< orphan*/  il_is_channel_valid (struct il_channel_info const*) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 

__attribute__((used)) static int
il4965_get_channels_for_scan(struct il_priv *il, struct ieee80211_vif *vif,
			     enum nl80211_band band, u8 is_active,
			     u8 n_probes, struct il_scan_channel *scan_ch)
{
	struct ieee80211_channel *chan;
	const struct ieee80211_supported_band *sband;
	const struct il_channel_info *ch_info;
	u16 passive_dwell = 0;
	u16 active_dwell = 0;
	int added, i;
	u16 channel;

	sband = il_get_hw_mode(il, band);
	if (!sband)
		return 0;

	active_dwell = il_get_active_dwell_time(il, band, n_probes);
	passive_dwell = il_get_passive_dwell_time(il, band, vif);

	if (passive_dwell <= active_dwell)
		passive_dwell = active_dwell + 1;

	for (i = 0, added = 0; i < il->scan_request->n_channels; i++) {
		chan = il->scan_request->channels[i];

		if (chan->band != band)
			continue;

		channel = chan->hw_value;
		scan_ch->channel = cpu_to_le16(channel);

		ch_info = il_get_channel_info(il, band, channel);
		if (!il_is_channel_valid(ch_info)) {
			D_SCAN("Channel %d is INVALID for this band.\n",
			       channel);
			continue;
		}

		if (!is_active || il_is_channel_passive(ch_info) ||
		    (chan->flags & IEEE80211_CHAN_NO_IR))
			scan_ch->type = SCAN_CHANNEL_TYPE_PASSIVE;
		else
			scan_ch->type = SCAN_CHANNEL_TYPE_ACTIVE;

		if (n_probes)
			scan_ch->type |= IL_SCAN_PROBE_MASK(n_probes);

		scan_ch->active_dwell = cpu_to_le16(active_dwell);
		scan_ch->passive_dwell = cpu_to_le16(passive_dwell);

		/* Set txpower levels to defaults */
		scan_ch->dsp_atten = 110;

		/* NOTE: if we were doing 6Mb OFDM for scans we'd use
		 * power level:
		 * scan_ch->tx_gain = ((1 << 5) | (2 << 3)) | 3;
		 */
		if (band == NL80211_BAND_5GHZ)
			scan_ch->tx_gain = ((1 << 5) | (3 << 3)) | 3;
		else
			scan_ch->tx_gain = ((1 << 5) | (5 << 3));

		D_SCAN("Scanning ch=%d prob=0x%X [%s %d]\n", channel,
		       le32_to_cpu(scan_ch->type),
		       (scan_ch->
			type & SCAN_CHANNEL_TYPE_ACTIVE) ? "ACTIVE" : "PASSIVE",
		       (scan_ch->
			type & SCAN_CHANNEL_TYPE_ACTIVE) ? active_dwell :
		       passive_dwell);

		scan_ch++;
		added++;
	}

	D_SCAN("total channels to scan %d\n", added);
	return added;
}