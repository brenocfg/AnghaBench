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
struct ieee80211_channel {int flags; } ;
struct brcmu_chan {scalar_t__ sb; } ;

/* Variables and functions */
 scalar_t__ BRCMU_CHAN_SB_U ; 
 int IEEE80211_CHAN_NO_HT40 ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 

__attribute__((used)) static void brcmf_update_bw40_channel_flag(struct ieee80211_channel *channel,
					   struct brcmu_chan *ch)
{
	u32 ht40_flag;

	ht40_flag = channel->flags & IEEE80211_CHAN_NO_HT40;
	if (ch->sb == BRCMU_CHAN_SB_U) {
		if (ht40_flag == IEEE80211_CHAN_NO_HT40)
			channel->flags &= ~IEEE80211_CHAN_NO_HT40;
		channel->flags |= IEEE80211_CHAN_NO_HT40PLUS;
	} else {
		/* It should be one of
		 * IEEE80211_CHAN_NO_HT40 or
		 * IEEE80211_CHAN_NO_HT40PLUS
		 */
		channel->flags &= ~IEEE80211_CHAN_NO_HT40;
		if (ht40_flag == IEEE80211_CHAN_NO_HT40)
			channel->flags |= IEEE80211_CHAN_NO_HT40MINUS;
	}
}