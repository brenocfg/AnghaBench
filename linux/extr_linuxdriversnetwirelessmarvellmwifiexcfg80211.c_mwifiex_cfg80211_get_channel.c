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
struct wireless_dev {int /*<<< orphan*/  netdev; } ;
struct wiphy {int dummy; } ;
struct mwifiex_bssdescriptor {int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; struct mwifiex_bssdescriptor bss_descriptor; } ;
struct cfg80211_chan_def {int dummy; } ;
struct mwifiex_private {scalar_t__ ht_param_present; TYPE_1__ curr_bss_params; scalar_t__ media_connected; struct cfg80211_chan_def bss_chandef; } ;
struct ieee80211_channel {int dummy; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 int NL80211_CHAN_NO_HT ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int) ; 
 scalar_t__ cfg80211_chandef_valid (struct cfg80211_chan_def*) ; 
 int ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 int mwifiex_band_to_radio_type (int /*<<< orphan*/ ) ; 
 int mwifiex_get_chan_type (struct mwifiex_private*) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_cfg80211_get_channel(struct wiphy *wiphy,
					struct wireless_dev *wdev,
					struct cfg80211_chan_def *chandef)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(wdev->netdev);
	struct mwifiex_bssdescriptor *curr_bss;
	struct ieee80211_channel *chan;
	enum nl80211_channel_type chan_type;
	enum nl80211_band band;
	int freq;
	int ret = -ENODATA;

	if (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP &&
	    cfg80211_chandef_valid(&priv->bss_chandef)) {
		*chandef = priv->bss_chandef;
		ret = 0;
	} else if (priv->media_connected) {
		curr_bss = &priv->curr_bss_params.bss_descriptor;
		band = mwifiex_band_to_radio_type(priv->curr_bss_params.band);
		freq = ieee80211_channel_to_frequency(curr_bss->channel, band);
		chan = ieee80211_get_channel(wiphy, freq);

		if (priv->ht_param_present) {
			chan_type = mwifiex_get_chan_type(priv);
			cfg80211_chandef_create(chandef, chan, chan_type);
		} else {
			cfg80211_chandef_create(chandef, chan,
						NL80211_CHAN_NO_HT);
		}
		ret = 0;
	}

	return ret;
}