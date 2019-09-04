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
typedef  int u16 ;
struct minstrel_rate_stats {int retry_updated; int prob_ewma; } ;
struct minstrel_priv {int dummy; } ;
struct minstrel_mcs_group_data {int /*<<< orphan*/  max_group_tp_rate; struct minstrel_rate_stats* rates; } ;
struct minstrel_ht_sta {scalar_t__ ampdu_packets; int sample_count; int* supported; int /*<<< orphan*/  last_stats_update; int /*<<< orphan*/  max_tp_rate; struct minstrel_mcs_group_data* groups; scalar_t__ sample_slow; scalar_t__ ampdu_len; int /*<<< orphan*/  avg_ampdu_len; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  EWMA_LEVEL ; 
 int MAX_THR_RATES ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 int /*<<< orphan*/  MINSTREL_FRAC (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  minstrel_calc_rate_stats (struct minstrel_rate_stats*) ; 
 int /*<<< orphan*/  minstrel_ewma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minstrel_ht_assign_best_tp_rates (struct minstrel_ht_sta*,int*,int*) ; 
 scalar_t__ minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,int,int,int) ; 
 int /*<<< orphan*/  minstrel_ht_prob_rate_reduce_streams (struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_set_best_prob_rate (struct minstrel_ht_sta*,int) ; 
 int /*<<< orphan*/  minstrel_ht_sort_best_tp_rates (struct minstrel_ht_sta*,int,int*) ; 
 int /*<<< orphan*/  minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_ht_update_stats(struct minstrel_priv *mp, struct minstrel_ht_sta *mi)
{
	struct minstrel_mcs_group_data *mg;
	struct minstrel_rate_stats *mrs;
	int group, i, j, cur_prob;
	u16 tmp_mcs_tp_rate[MAX_THR_RATES], tmp_group_tp_rate[MAX_THR_RATES];
	u16 tmp_cck_tp_rate[MAX_THR_RATES], index;

	if (mi->ampdu_packets > 0) {
		mi->avg_ampdu_len = minstrel_ewma(mi->avg_ampdu_len,
			MINSTREL_FRAC(mi->ampdu_len, mi->ampdu_packets), EWMA_LEVEL);
		mi->ampdu_len = 0;
		mi->ampdu_packets = 0;
	}

	mi->sample_slow = 0;
	mi->sample_count = 0;

	/* Initialize global rate indexes */
	for(j = 0; j < MAX_THR_RATES; j++){
		tmp_mcs_tp_rate[j] = 0;
		tmp_cck_tp_rate[j] = 0;
	}

	/* Find best rate sets within all MCS groups*/
	for (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) {

		mg = &mi->groups[group];
		if (!mi->supported[group])
			continue;

		mi->sample_count++;

		/* (re)Initialize group rate indexes */
		for(j = 0; j < MAX_THR_RATES; j++)
			tmp_group_tp_rate[j] = group;

		for (i = 0; i < MCS_GROUP_RATES; i++) {
			if (!(mi->supported[group] & BIT(i)))
				continue;

			index = MCS_GROUP_RATES * group + i;

			mrs = &mg->rates[i];
			mrs->retry_updated = false;
			minstrel_calc_rate_stats(mrs);
			cur_prob = mrs->prob_ewma;

			if (minstrel_ht_get_tp_avg(mi, group, i, cur_prob) == 0)
				continue;

			/* Find max throughput rate set */
			if (group != MINSTREL_CCK_GROUP) {
				minstrel_ht_sort_best_tp_rates(mi, index,
							       tmp_mcs_tp_rate);
			} else if (group == MINSTREL_CCK_GROUP) {
				minstrel_ht_sort_best_tp_rates(mi, index,
							       tmp_cck_tp_rate);
			}

			/* Find max throughput rate set within a group */
			minstrel_ht_sort_best_tp_rates(mi, index,
						       tmp_group_tp_rate);

			/* Find max probability rate per group and global */
			minstrel_ht_set_best_prob_rate(mi, index);
		}

		memcpy(mg->max_group_tp_rate, tmp_group_tp_rate,
		       sizeof(mg->max_group_tp_rate));
	}

	/* Assign new rate set per sta */
	minstrel_ht_assign_best_tp_rates(mi, tmp_mcs_tp_rate, tmp_cck_tp_rate);
	memcpy(mi->max_tp_rate, tmp_mcs_tp_rate, sizeof(mi->max_tp_rate));

	/* Try to increase robustness of max_prob_rate*/
	minstrel_ht_prob_rate_reduce_streams(mi);

	/* try to sample all available rates during each interval */
	mi->sample_count *= 8;

#ifdef CONFIG_MAC80211_DEBUGFS
	/* use fixed index if set */
	if (mp->fixed_rate_idx != -1) {
		for (i = 0; i < 4; i++)
			mi->max_tp_rate[i] = mp->fixed_rate_idx;
		mi->max_prob_rate = mp->fixed_rate_idx;
	}
#endif

	/* Reset update timer */
	mi->last_stats_update = jiffies;
}