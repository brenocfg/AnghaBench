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
struct minstrel_sta_info {int /*<<< orphan*/  sta; int /*<<< orphan*/  lowest_rix; int /*<<< orphan*/  max_prob_rate; int /*<<< orphan*/ * max_tp_rate; } ;
struct minstrel_priv {TYPE_2__* hw; int /*<<< orphan*/  max_retry; } ;
struct ieee80211_sta_rates {TYPE_1__* rate; } ;
struct TYPE_4__ {int max_rates; } ;
struct TYPE_3__ {int /*<<< orphan*/  count_rts; int /*<<< orphan*/  count_cts; int /*<<< orphan*/  count; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_sta_rates* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minstrel_set_rate (struct minstrel_sta_info*,struct ieee80211_sta_rates*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_control_set_rates (TYPE_2__*,int /*<<< orphan*/ ,struct ieee80211_sta_rates*) ; 

__attribute__((used)) static void
minstrel_update_rates(struct minstrel_priv *mp, struct minstrel_sta_info *mi)
{
	struct ieee80211_sta_rates *ratetbl;
	int i = 0;

	ratetbl = kzalloc(sizeof(*ratetbl), GFP_ATOMIC);
	if (!ratetbl)
		return;

	/* Start with max_tp_rate */
	minstrel_set_rate(mi, ratetbl, i++, mi->max_tp_rate[0]);

	if (mp->hw->max_rates >= 3) {
		/* At least 3 tx rates supported, use max_tp_rate2 next */
		minstrel_set_rate(mi, ratetbl, i++, mi->max_tp_rate[1]);
	}

	if (mp->hw->max_rates >= 2) {
		/* At least 2 tx rates supported, use max_prob_rate next */
		minstrel_set_rate(mi, ratetbl, i++, mi->max_prob_rate);
	}

	/* Use lowest rate last */
	ratetbl->rate[i].idx = mi->lowest_rix;
	ratetbl->rate[i].count = mp->max_retry;
	ratetbl->rate[i].count_cts = mp->max_retry;
	ratetbl->rate[i].count_rts = mp->max_retry;

	rate_control_set_rates(mp->hw, mi->sta, ratetbl);
}