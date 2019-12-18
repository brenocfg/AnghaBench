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
struct minstrel_rate_stats {int dummy; } ;
struct minstrel_priv {scalar_t__* cck_rates; } ;
struct minstrel_ht_sta {int* supported; TYPE_1__* groups; } ;
struct ieee80211_tx_rate {int flags; int idx; } ;
struct TYPE_2__ {struct minstrel_rate_stats* rates; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int BIT (int) ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int MINSTREL_CCK_GROUP ; 
 int ieee80211_rate_get_vht_mcs (struct ieee80211_tx_rate*) ; 
 int minstrel_ht_get_group_idx (struct ieee80211_tx_rate*) ; 
 int minstrel_vht_get_group_idx (struct ieee80211_tx_rate*) ; 

__attribute__((used)) static struct minstrel_rate_stats *
minstrel_ht_get_stats(struct minstrel_priv *mp, struct minstrel_ht_sta *mi,
		      struct ieee80211_tx_rate *rate)
{
	int group, idx;

	if (rate->flags & IEEE80211_TX_RC_MCS) {
		group = minstrel_ht_get_group_idx(rate);
		idx = rate->idx % 8;
	} else if (rate->flags & IEEE80211_TX_RC_VHT_MCS) {
		group = minstrel_vht_get_group_idx(rate);
		idx = ieee80211_rate_get_vht_mcs(rate);
	} else {
		group = MINSTREL_CCK_GROUP;

		for (idx = 0; idx < ARRAY_SIZE(mp->cck_rates); idx++)
			if (rate->idx == mp->cck_rates[idx])
				break;

		/* short preamble */
		if ((mi->supported[group] & BIT(idx + 4)) &&
		    (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE))
			idx += 4;
	}
	return &mi->groups[group].rates[idx];
}