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
typedef  void* u8 ;
typedef  int u16 ;
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  iftype; } ;
struct ieee80211_sub_if_data {TYPE_3__ wdev; TYPE_2__* local; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_4__ {struct wiphy* wiphy; } ;
struct TYPE_5__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfg80211_reg_can_beacon_relax (struct wiphy*,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 void* ieee80211_frequency_to_channel (int) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 void** skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static u8
ieee80211_tdls_add_subband(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb, u16 start, u16 end,
			   u16 spacing)
{
	u8 subband_cnt = 0, ch_cnt = 0;
	struct ieee80211_channel *ch;
	struct cfg80211_chan_def chandef;
	int i, subband_start;
	struct wiphy *wiphy = sdata->local->hw.wiphy;

	for (i = start; i <= end; i += spacing) {
		if (!ch_cnt)
			subband_start = i;

		ch = ieee80211_get_channel(sdata->local->hw.wiphy, i);
		if (ch) {
			/* we will be active on the channel */
			cfg80211_chandef_create(&chandef, ch,
						NL80211_CHAN_NO_HT);
			if (cfg80211_reg_can_beacon_relax(wiphy, &chandef,
							  sdata->wdev.iftype)) {
				ch_cnt++;
				/*
				 * check if the next channel is also part of
				 * this allowed range
				 */
				continue;
			}
		}

		/*
		 * we've reached the end of a range, with allowed channels
		 * found
		 */
		if (ch_cnt) {
			u8 *pos = skb_put(skb, 2);
			*pos++ = ieee80211_frequency_to_channel(subband_start);
			*pos++ = ch_cnt;

			subband_cnt++;
			ch_cnt = 0;
		}
	}

	/* all channels in the requested range are allowed - add them here */
	if (ch_cnt) {
		u8 *pos = skb_put(skb, 2);
		*pos++ = ieee80211_frequency_to_channel(subband_start);
		*pos++ = ch_cnt;

		subband_cnt++;
	}

	return subband_cnt;
}