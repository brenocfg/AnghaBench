#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct minstrel_priv {int fixed_rate_idx; int* cck_rates; TYPE_2__* hw; } ;
struct minstrel_ht_sta {int max_prob_rate; int tx_flags; scalar_t__ sample_packets; int /*<<< orphan*/  total_packets; } ;
struct minstrel_ht_sta_priv {int /*<<< orphan*/  legacy; int /*<<< orphan*/  is_ht; struct minstrel_ht_sta ht; } ;
struct mcs_group {int flags; int streams; } ;
struct ieee80211_tx_rate_control {int short_preamble; int /*<<< orphan*/  skb; } ;
struct ieee80211_tx_rate {int count; int idx; int flags; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_3__ control; TYPE_1__ status; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_8__ {void (* get_rate ) (void*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct ieee80211_tx_rate_control*) ;} ;
struct TYPE_6__ {int max_rates; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (int /*<<< orphan*/ ) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_CTRL_PORT_CTRL_PROTO ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 int /*<<< orphan*/  ieee80211_rate_set_vht (struct ieee80211_tx_rate*,int,int) ; 
 TYPE_4__ mac80211_minstrel ; 
 int /*<<< orphan*/  minstrel_aggr_check (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int minstrel_get_sample_rate (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 struct mcs_group const* minstrel_mcs_groups ; 
 void stub1 (void*,struct ieee80211_sta*,int /*<<< orphan*/ *,struct ieee80211_tx_rate_control*) ; 

__attribute__((used)) static void
minstrel_ht_get_rate(void *priv, struct ieee80211_sta *sta, void *priv_sta,
                     struct ieee80211_tx_rate_control *txrc)
{
	const struct mcs_group *sample_group;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	struct ieee80211_tx_rate *rate = &info->status.rates[0];
	struct minstrel_ht_sta_priv *msp = priv_sta;
	struct minstrel_ht_sta *mi = &msp->ht;
	struct minstrel_priv *mp = priv;
	int sample_idx;

	if (!msp->is_ht)
		return mac80211_minstrel.get_rate(priv, sta, &msp->legacy, txrc);

	if (!(info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    mi->max_prob_rate / MCS_GROUP_RATES != MINSTREL_CCK_GROUP)
		minstrel_aggr_check(sta, txrc->skb);

	info->flags |= mi->tx_flags;

#ifdef CONFIG_MAC80211_DEBUGFS
	if (mp->fixed_rate_idx != -1)
		return;
#endif

	/* Don't use EAPOL frames for sampling on non-mrr hw */
	if (mp->hw->max_rates == 1 &&
	    (info->control.flags & IEEE80211_TX_CTRL_PORT_CTRL_PROTO))
		sample_idx = -1;
	else
		sample_idx = minstrel_get_sample_rate(mp, mi);

	mi->total_packets++;

	/* wraparound */
	if (mi->total_packets == ~0) {
		mi->total_packets = 0;
		mi->sample_packets = 0;
	}

	if (sample_idx < 0)
		return;

	sample_group = &minstrel_mcs_groups[sample_idx / MCS_GROUP_RATES];
	sample_idx %= MCS_GROUP_RATES;

	if (sample_group == &minstrel_mcs_groups[MINSTREL_CCK_GROUP] &&
	    (sample_idx >= 4) != txrc->short_preamble)
		return;

	info->flags |= IEEE80211_TX_CTL_RATE_CTRL_PROBE;
	rate->count = 1;

	if (sample_group == &minstrel_mcs_groups[MINSTREL_CCK_GROUP]) {
		int idx = sample_idx % ARRAY_SIZE(mp->cck_rates);
		rate->idx = mp->cck_rates[idx];
	} else if (sample_group->flags & IEEE80211_TX_RC_VHT_MCS) {
		ieee80211_rate_set_vht(rate, sample_idx % MCS_GROUP_RATES,
				       sample_group->streams);
	} else {
		rate->idx = sample_idx + (sample_group->streams - 1) * 8;
	}

	rate->flags = sample_group->flags;
}