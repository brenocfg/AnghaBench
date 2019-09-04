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
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct ieee80211_supported_band {unsigned int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_regdomain {int dummy; } ;
struct ieee80211_reg_rule {int flags; } ;
struct ieee80211_channel {size_t band; int center_freq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40 ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40MINUS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_HT40PLUS ; 
 int /*<<< orphan*/  IS_ERR (struct ieee80211_reg_rule const*) ; 
 int /*<<< orphan*/  MHZ_TO_KHZ (int) ; 
 int NL80211_RRF_NO_HT40MINUS ; 
 int NL80211_RRF_NO_HT40PLUS ; 
 struct ieee80211_reg_rule* freq_reg_info_regd (int /*<<< orphan*/ ,struct ieee80211_regdomain const*,int /*<<< orphan*/ ) ; 
 struct ieee80211_regdomain* get_wiphy_regdom (struct wiphy*) ; 
 int /*<<< orphan*/  is_ht40_allowed (struct ieee80211_channel*) ; 

__attribute__((used)) static void reg_process_ht_flags_channel(struct wiphy *wiphy,
					 struct ieee80211_channel *channel)
{
	struct ieee80211_supported_band *sband = wiphy->bands[channel->band];
	struct ieee80211_channel *channel_before = NULL, *channel_after = NULL;
	const struct ieee80211_regdomain *regd;
	unsigned int i;
	u32 flags;

	if (!is_ht40_allowed(channel)) {
		channel->flags |= IEEE80211_CHAN_NO_HT40;
		return;
	}

	/*
	 * We need to ensure the extension channels exist to
	 * be able to use HT40- or HT40+, this finds them (or not)
	 */
	for (i = 0; i < sband->n_channels; i++) {
		struct ieee80211_channel *c = &sband->channels[i];

		if (c->center_freq == (channel->center_freq - 20))
			channel_before = c;
		if (c->center_freq == (channel->center_freq + 20))
			channel_after = c;
	}

	flags = 0;
	regd = get_wiphy_regdom(wiphy);
	if (regd) {
		const struct ieee80211_reg_rule *reg_rule =
			freq_reg_info_regd(MHZ_TO_KHZ(channel->center_freq),
					   regd, MHZ_TO_KHZ(20));

		if (!IS_ERR(reg_rule))
			flags = reg_rule->flags;
	}

	/*
	 * Please note that this assumes target bandwidth is 20 MHz,
	 * if that ever changes we also need to change the below logic
	 * to include that as well.
	 */
	if (!is_ht40_allowed(channel_before) ||
	    flags & NL80211_RRF_NO_HT40MINUS)
		channel->flags |= IEEE80211_CHAN_NO_HT40MINUS;
	else
		channel->flags &= ~IEEE80211_CHAN_NO_HT40MINUS;

	if (!is_ht40_allowed(channel_after) ||
	    flags & NL80211_RRF_NO_HT40PLUS)
		channel->flags |= IEEE80211_CHAN_NO_HT40PLUS;
	else
		channel->flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
}