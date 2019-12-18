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
typedef  size_t u8 ;
struct minstrel_sta_info {int n_rates; int* max_tp_rate; size_t max_prob_rate; int /*<<< orphan*/  last_stats_update; struct minstrel_rate* r; } ;
struct minstrel_rate_stats {scalar_t__ prob_ewma; int retry_count; } ;
struct minstrel_rate {int adjusted_retry_count; int sample_limit; struct minstrel_rate_stats stats; } ;
struct minstrel_priv {int fixed_rate_idx; } ;

/* Variables and functions */
 int MAX_THR_RATES ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int*,size_t*,int) ; 
 int /*<<< orphan*/  minstrel_calc_rate_stats (struct minstrel_rate_stats*) ; 
 int minstrel_get_tp_avg (struct minstrel_rate*,scalar_t__) ; 
 int /*<<< orphan*/  minstrel_sort_best_tp_rates (struct minstrel_sta_info*,int,size_t*) ; 
 int /*<<< orphan*/  minstrel_update_rates (struct minstrel_priv*,struct minstrel_sta_info*) ; 

__attribute__((used)) static void
minstrel_update_stats(struct minstrel_priv *mp, struct minstrel_sta_info *mi)
{
	u8 tmp_tp_rate[MAX_THR_RATES];
	u8 tmp_prob_rate = 0;
	int i, tmp_cur_tp, tmp_prob_tp;

	for (i = 0; i < MAX_THR_RATES; i++)
	    tmp_tp_rate[i] = 0;

	for (i = 0; i < mi->n_rates; i++) {
		struct minstrel_rate *mr = &mi->r[i];
		struct minstrel_rate_stats *mrs = &mi->r[i].stats;
		struct minstrel_rate_stats *tmp_mrs = &mi->r[tmp_prob_rate].stats;

		/* Update statistics of success probability per rate */
		minstrel_calc_rate_stats(mrs);

		/* Sample less often below the 10% chance of success.
		 * Sample less often above the 95% chance of success. */
		if (mrs->prob_ewma > MINSTREL_FRAC(95, 100) ||
		    mrs->prob_ewma < MINSTREL_FRAC(10, 100)) {
			mr->adjusted_retry_count = mrs->retry_count >> 1;
			if (mr->adjusted_retry_count > 2)
				mr->adjusted_retry_count = 2;
			mr->sample_limit = 4;
		} else {
			mr->sample_limit = -1;
			mr->adjusted_retry_count = mrs->retry_count;
		}
		if (!mr->adjusted_retry_count)
			mr->adjusted_retry_count = 2;

		minstrel_sort_best_tp_rates(mi, i, tmp_tp_rate);

		/* To determine the most robust rate (max_prob_rate) used at
		 * 3rd mmr stage we distinct between two cases:
		 * (1) if any success probabilitiy >= 95%, out of those rates
		 * choose the maximum throughput rate as max_prob_rate
		 * (2) if all success probabilities < 95%, the rate with
		 * highest success probability is chosen as max_prob_rate */
		if (mrs->prob_ewma >= MINSTREL_FRAC(95, 100)) {
			tmp_cur_tp = minstrel_get_tp_avg(mr, mrs->prob_ewma);
			tmp_prob_tp = minstrel_get_tp_avg(&mi->r[tmp_prob_rate],
							  tmp_mrs->prob_ewma);
			if (tmp_cur_tp >= tmp_prob_tp)
				tmp_prob_rate = i;
		} else {
			if (mrs->prob_ewma >= tmp_mrs->prob_ewma)
				tmp_prob_rate = i;
		}
	}

	/* Assign the new rate set */
	memcpy(mi->max_tp_rate, tmp_tp_rate, sizeof(mi->max_tp_rate));
	mi->max_prob_rate = tmp_prob_rate;

#ifdef CONFIG_MAC80211_DEBUGFS
	/* use fixed index if set */
	if (mp->fixed_rate_idx != -1) {
		mi->max_tp_rate[0] = mp->fixed_rate_idx;
		mi->max_tp_rate[1] = mp->fixed_rate_idx;
		mi->max_prob_rate = mp->fixed_rate_idx;
	}
#endif

	/* Reset update timer */
	mi->last_stats_update = jiffies;

	minstrel_update_rates(mp, mi);
}