#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mwifiex_uap_bss_param {int band_cfg; int /*<<< orphan*/  channel; } ;
struct cfg80211_chan_def {int width; TYPE_1__* chan; int /*<<< orphan*/  center_freq1; } ;
struct mwifiex_private {TYPE_2__* adapter; struct cfg80211_chan_def bss_chandef; } ;
struct TYPE_4__ {int config_bands; int /*<<< orphan*/  wiphy; } ;
struct TYPE_3__ {scalar_t__ band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int BAND_A ; 
 int BAND_AAC ; 
 int BAND_AN ; 
 int BAND_B ; 
 int BAND_CONFIG_A ; 
 int BAND_CONFIG_BG ; 
 int BAND_G ; 
 int BAND_GN ; 
 int MWIFIEX_SEC_CHAN_ABOVE ; 
 int MWIFIEX_SEC_CHAN_BELOW ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_160 134 
#define  NL80211_CHAN_WIDTH_20 133 
#define  NL80211_CHAN_WIDTH_20_NOHT 132 
#define  NL80211_CHAN_WIDTH_40 131 
#define  NL80211_CHAN_WIDTH_5 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WARN ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mwifiex_dnld_txpwr_table (struct mwifiex_private*) ; 
 int mwifiex_get_sec_chan_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_send_domain_info_cmd_fw (int /*<<< orphan*/ ) ; 

void mwifiex_uap_set_channel(struct mwifiex_private *priv,
			     struct mwifiex_uap_bss_param *bss_cfg,
			     struct cfg80211_chan_def chandef)
{
	u8 config_bands = 0, old_bands = priv->adapter->config_bands;

	priv->bss_chandef = chandef;

	bss_cfg->channel = ieee80211_frequency_to_channel(
						     chandef.chan->center_freq);

	/* Set appropriate bands */
	if (chandef.chan->band == NL80211_BAND_2GHZ) {
		bss_cfg->band_cfg = BAND_CONFIG_BG;
		config_bands = BAND_B | BAND_G;

		if (chandef.width > NL80211_CHAN_WIDTH_20_NOHT)
			config_bands |= BAND_GN;
	} else {
		bss_cfg->band_cfg = BAND_CONFIG_A;
		config_bands = BAND_A;

		if (chandef.width > NL80211_CHAN_WIDTH_20_NOHT)
			config_bands |= BAND_AN;

		if (chandef.width > NL80211_CHAN_WIDTH_40)
			config_bands |= BAND_AAC;
	}

	switch (chandef.width) {
	case NL80211_CHAN_WIDTH_5:
	case NL80211_CHAN_WIDTH_10:
	case NL80211_CHAN_WIDTH_20_NOHT:
	case NL80211_CHAN_WIDTH_20:
		break;
	case NL80211_CHAN_WIDTH_40:
		if (chandef.center_freq1 < chandef.chan->center_freq)
			bss_cfg->band_cfg |= MWIFIEX_SEC_CHAN_BELOW;
		else
			bss_cfg->band_cfg |= MWIFIEX_SEC_CHAN_ABOVE;
		break;
	case NL80211_CHAN_WIDTH_80:
	case NL80211_CHAN_WIDTH_80P80:
	case NL80211_CHAN_WIDTH_160:
		bss_cfg->band_cfg |=
		    mwifiex_get_sec_chan_offset(bss_cfg->channel) << 4;
		break;
	default:
		mwifiex_dbg(priv->adapter,
			    WARN, "Unknown channel width: %d\n",
			    chandef.width);
		break;
	}

	priv->adapter->config_bands = config_bands;

	if (old_bands != config_bands) {
		mwifiex_send_domain_info_cmd_fw(priv->adapter->wiphy);
		mwifiex_dnld_txpwr_table(priv);
	}
}