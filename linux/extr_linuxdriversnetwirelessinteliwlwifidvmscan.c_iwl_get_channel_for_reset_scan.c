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
typedef  scalar_t__ u16 ;
struct iwl_scan_channel {int dsp_atten; int tx_gain; void* passive_dwell; void* active_dwell; int /*<<< orphan*/  type; void* channel; } ;
struct iwl_priv {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_supported_band {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_RADIO_RESET_DWELL_TIME ; 
 int NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SCAN_CHANNEL_TYPE_PASSIVE ; 
 void* cpu_to_le16 (scalar_t__) ; 
 struct ieee80211_supported_band* iwl_get_hw_mode (struct iwl_priv*,int) ; 
 scalar_t__ iwl_get_single_channel_number (struct iwl_priv*,int) ; 

__attribute__((used)) static int iwl_get_channel_for_reset_scan(struct iwl_priv *priv,
					  struct ieee80211_vif *vif,
					  enum nl80211_band band,
					  struct iwl_scan_channel *scan_ch)
{
	const struct ieee80211_supported_band *sband;
	u16 channel;

	sband = iwl_get_hw_mode(priv, band);
	if (!sband) {
		IWL_ERR(priv, "invalid band\n");
		return 0;
	}

	channel = iwl_get_single_channel_number(priv, band);
	if (channel) {
		scan_ch->channel = cpu_to_le16(channel);
		scan_ch->type = SCAN_CHANNEL_TYPE_PASSIVE;
		scan_ch->active_dwell =
			cpu_to_le16(IWL_RADIO_RESET_DWELL_TIME);
		scan_ch->passive_dwell =
			cpu_to_le16(IWL_RADIO_RESET_DWELL_TIME);
		/* Set txpower levels to defaults */
		scan_ch->dsp_atten = 110;
		if (band == NL80211_BAND_5GHZ)
			scan_ch->tx_gain = ((1 << 5) | (3 << 3)) | 3;
		else
			scan_ch->tx_gain = ((1 << 5) | (5 << 3));
		return 1;
	}

	IWL_ERR(priv, "no valid channel found\n");
	return 0;
}