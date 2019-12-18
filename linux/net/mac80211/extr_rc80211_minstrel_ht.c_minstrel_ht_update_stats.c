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
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  tmp_mcs_tp_rate ;
typedef  int /*<<< orphan*/  tmp_cck_tp_rate ;
struct minstrel_rate_stats {int retry_updated; int prob_ewma; } ;
struct minstrel_priv {int sample_switch; int fixed_rate_idx; int /*<<< orphan*/  hw; } ;
struct minstrel_mcs_group_data {int* max_group_tp_rate; struct minstrel_rate_stats* rates; } ;
struct minstrel_ht_sta {scalar_t__ total_packets_cur; scalar_t__ total_packets; scalar_t__ total_packets_last; scalar_t__ ampdu_packets; int sample_count; int* supported; int* max_tp_rate; int max_prob_rate; int /*<<< orphan*/  last_stats_update; void* sample_mode; struct minstrel_mcs_group_data* groups; scalar_t__ sample_slow; scalar_t__ ampdu_len; scalar_t__ avg_ampdu_len; } ;

/* Variables and functions */
 int ARRAY_SIZE (size_t*) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  EWMA_LEVEL ; 
 int MAX_THR_RATES ; 
 size_t MCS_GROUP_RATES ; 
 size_t MINSTREL_CCK_GROUP ; 
 int /*<<< orphan*/  MINSTREL_FRAC (scalar_t__,scalar_t__) ; 
 size_t MINSTREL_HT_GROUP_0 ; 
 void* MINSTREL_SAMPLE_IDLE ; 
 size_t MINSTREL_VHT_GROUP_0 ; 
 scalar_t__ SAMPLE_SWITCH_THR ; 
 int /*<<< orphan*/  TX_STATUS_NO_AMPDU_LEN ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int*,size_t*,int) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  minstrel_calc_rate_stats (struct minstrel_rate_stats*) ; 
 scalar_t__ minstrel_ewma (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minstrel_ht_assign_best_tp_rates (struct minstrel_ht_sta*,size_t*,size_t*) ; 
 scalar_t__ minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,int,int,int) ; 
 int /*<<< orphan*/  minstrel_ht_prob_rate_reduce_streams (struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_rate_sample_switch (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_set_best_prob_rate (struct minstrel_ht_sta*,size_t) ; 
 int /*<<< orphan*/  minstrel_ht_sort_best_tp_rates (struct minstrel_ht_sta*,size_t,size_t*) ; 
 size_t* minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_ht_update_stats(struct minstrel_priv *mp, struct minstrel_ht_sta *mi,
			 bool sample)
{
	struct minstrel_mcs_group_data *mg;
	struct minstrel_rate_stats *mrs;
	int group, i, j, cur_prob;
	u16 tmp_mcs_tp_rate[MAX_THR_RATES], tmp_group_tp_rate[MAX_THR_RATES];
	u16 tmp_cck_tp_rate[MAX_THR_RATES], index;

	mi->sample_mode = MINSTREL_SAMPLE_IDLE;

	if (sample) {
		mi->total_packets_cur = mi->total_packets -
					mi->total_packets_last;
		mi->total_packets_last = mi->total_packets;
	}
	if (!mp->sample_switch)
		sample = false;
	if (mi->total_packets_cur < SAMPLE_SWITCH_THR && mp->sample_switch != 1)
	    sample = false;

	if (mi->ampdu_packets > 0) {
		if (!ieee80211_hw_check(mp->hw, TX_STATUS_NO_AMPDU_LEN))
			mi->avg_ampdu_len = minstrel_ewma(mi->avg_ampdu_len,
				MINSTREL_FRAC(mi->ampdu_len, mi->ampdu_packets),
					      EWMA_LEVEL);
		else
			mi->avg_ampdu_len = 0;
		mi->ampdu_len = 0;
		mi->ampdu_packets = 0;
	}

	mi->sample_slow = 0;
	mi->sample_count = 0;

	memset(tmp_mcs_tp_rate, 0, sizeof(tmp_mcs_tp_rate));
	memset(tmp_cck_tp_rate, 0, sizeof(tmp_cck_tp_rate));
	if (mi->supported[MINSTREL_CCK_GROUP])
		for (j = 0; j < ARRAY_SIZE(tmp_cck_tp_rate); j++)
			tmp_cck_tp_rate[j] = MINSTREL_CCK_GROUP * MCS_GROUP_RATES;

	if (mi->supported[MINSTREL_VHT_GROUP_0])
		index = MINSTREL_VHT_GROUP_0 * MCS_GROUP_RATES;
	else
		index = MINSTREL_HT_GROUP_0 * MCS_GROUP_RATES;

	for (j = 0; j < ARRAY_SIZE(tmp_mcs_tp_rate); j++)
		tmp_mcs_tp_rate[j] = index;

	/* Find best rate sets within all MCS groups*/
	for (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) {

		mg = &mi->groups[group];
		if (!mi->supported[group])
			continue;

		mi->sample_count++;

		/* (re)Initialize group rate indexes */
		for(j = 0; j < MAX_THR_RATES; j++)
			tmp_group_tp_rate[j] = MCS_GROUP_RATES * group;

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

	if (sample)
		minstrel_ht_rate_sample_switch(mp, mi);

#ifdef CONFIG_MAC80211_DEBUGFS
	/* use fixed index if set */
	if (mp->fixed_rate_idx != -1) {
		for (i = 0; i < 4; i++)
			mi->max_tp_rate[i] = mp->fixed_rate_idx;
		mi->max_prob_rate = mp->fixed_rate_idx;
		mi->sample_mode = MINSTREL_SAMPLE_IDLE;
	}
#endif

	/* Reset update timer */
	mi->last_stats_update = jiffies;
}