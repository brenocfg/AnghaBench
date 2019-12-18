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
typedef  int /*<<< orphan*/  u16 ;
struct minstrel_priv {TYPE_2__* hw; } ;
struct minstrel_ht_sta {scalar_t__ sample_mode; TYPE_3__* sta; int /*<<< orphan*/  max_prob_rate; int /*<<< orphan*/ * max_tp_rate; int /*<<< orphan*/  sample_rate; } ;
struct ieee80211_sta_rates {TYPE_1__* rate; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_rc_amsdu_len; } ;
struct TYPE_5__ {int max_rates; } ;
struct TYPE_4__ {int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MINSTREL_SAMPLE_ACTIVE ; 
 struct ieee80211_sta_rates* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minstrel_ht_get_max_amsdu_len (struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_set_rate (struct minstrel_priv*,struct minstrel_ht_sta*,struct ieee80211_sta_rates*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_control_set_rates (TYPE_2__*,TYPE_3__*,struct ieee80211_sta_rates*) ; 

__attribute__((used)) static void
minstrel_ht_update_rates(struct minstrel_priv *mp, struct minstrel_ht_sta *mi)
{
	struct ieee80211_sta_rates *rates;
	u16 first_rate = mi->max_tp_rate[0];
	int i = 0;

	if (mi->sample_mode == MINSTREL_SAMPLE_ACTIVE)
		first_rate = mi->sample_rate;

	rates = kzalloc(sizeof(*rates), GFP_ATOMIC);
	if (!rates)
		return;

	/* Start with max_tp_rate[0] */
	minstrel_ht_set_rate(mp, mi, rates, i++, first_rate);

	if (mp->hw->max_rates >= 3) {
		/* At least 3 tx rates supported, use max_tp_rate[1] next */
		minstrel_ht_set_rate(mp, mi, rates, i++, mi->max_tp_rate[1]);
	}

	if (mp->hw->max_rates >= 2) {
		minstrel_ht_set_rate(mp, mi, rates, i++, mi->max_prob_rate);
	}

	mi->sta->max_rc_amsdu_len = minstrel_ht_get_max_amsdu_len(mi);
	rates->rate[i].idx = -1;
	rate_control_set_rates(mp->hw, mi->sta, rates);
}