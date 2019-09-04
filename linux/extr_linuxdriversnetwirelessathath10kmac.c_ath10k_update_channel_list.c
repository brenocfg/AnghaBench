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
struct wmi_scan_chan_list_arg {int n_channels; struct wmi_channel_arg* channels; int /*<<< orphan*/  member_0; } ;
struct wmi_channel_arg {int allow_ht; int allow_vht; int allow_ibss; int ht40plus; int chan_radar; int passive; int max_power; int max_reg_power; int max_antenna_gain; scalar_t__ mode; int /*<<< orphan*/  freq; scalar_t__ reg_class_id; scalar_t__ min_power; int /*<<< orphan*/  band_center_freq1; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_hw {TYPE_1__* wiphy; } ;
struct ieee80211_channel {int flags; int max_power; int max_reg_power; int max_antenna_gain; scalar_t__ band; int /*<<< orphan*/  center_freq; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; struct ieee80211_hw* hw; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ MODE_11A ; 
 scalar_t__ MODE_11G ; 
 scalar_t__ MODE_UNKNOWN ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int NUM_NL80211_BANDS ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int,int,int,scalar_t__) ; 
 int ath10k_wmi_scan_chan_list (struct ath10k*,struct wmi_scan_chan_list_arg*) ; 
 int /*<<< orphan*/  kfree (struct wmi_channel_arg*) ; 
 struct wmi_channel_arg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_update_channel_list(struct ath10k *ar)
{
	struct ieee80211_hw *hw = ar->hw;
	struct ieee80211_supported_band **bands;
	enum nl80211_band band;
	struct ieee80211_channel *channel;
	struct wmi_scan_chan_list_arg arg = {0};
	struct wmi_channel_arg *ch;
	bool passive;
	int len;
	int ret;
	int i;

	lockdep_assert_held(&ar->conf_mutex);

	bands = hw->wiphy->bands;
	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		if (!bands[band])
			continue;

		for (i = 0; i < bands[band]->n_channels; i++) {
			if (bands[band]->channels[i].flags &
			    IEEE80211_CHAN_DISABLED)
				continue;

			arg.n_channels++;
		}
	}

	len = sizeof(struct wmi_channel_arg) * arg.n_channels;
	arg.channels = kzalloc(len, GFP_KERNEL);
	if (!arg.channels)
		return -ENOMEM;

	ch = arg.channels;
	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		if (!bands[band])
			continue;

		for (i = 0; i < bands[band]->n_channels; i++) {
			channel = &bands[band]->channels[i];

			if (channel->flags & IEEE80211_CHAN_DISABLED)
				continue;

			ch->allow_ht = true;

			/* FIXME: when should we really allow VHT? */
			ch->allow_vht = true;

			ch->allow_ibss =
				!(channel->flags & IEEE80211_CHAN_NO_IR);

			ch->ht40plus =
				!(channel->flags & IEEE80211_CHAN_NO_HT40PLUS);

			ch->chan_radar =
				!!(channel->flags & IEEE80211_CHAN_RADAR);

			passive = channel->flags & IEEE80211_CHAN_NO_IR;
			ch->passive = passive;

			/* the firmware is ignoring the "radar" flag of the
			 * channel and is scanning actively using Probe Requests
			 * on "Radar detection"/DFS channels which are not
			 * marked as "available"
			 */
			ch->passive |= ch->chan_radar;

			ch->freq = channel->center_freq;
			ch->band_center_freq1 = channel->center_freq;
			ch->min_power = 0;
			ch->max_power = channel->max_power * 2;
			ch->max_reg_power = channel->max_reg_power * 2;
			ch->max_antenna_gain = channel->max_antenna_gain * 2;
			ch->reg_class_id = 0; /* FIXME */

			/* FIXME: why use only legacy modes, why not any
			 * HT/VHT modes? Would that even make any
			 * difference?
			 */
			if (channel->band == NL80211_BAND_2GHZ)
				ch->mode = MODE_11G;
			else
				ch->mode = MODE_11A;

			if (WARN_ON_ONCE(ch->mode == MODE_UNKNOWN))
				continue;

			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "mac channel [%zd/%d] freq %d maxpower %d regpower %d antenna %d mode %d\n",
				    ch - arg.channels, arg.n_channels,
				   ch->freq, ch->max_power, ch->max_reg_power,
				   ch->max_antenna_gain, ch->mode);

			ch++;
		}
	}

	ret = ath10k_wmi_scan_chan_list(ar, &arg);
	kfree(arg.channels);

	return ret;
}