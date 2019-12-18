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
struct minstrel_rate_stats {scalar_t__ prob_ewma; int sample_skipped; scalar_t__ attempts; } ;
struct minstrel_priv {int sample_switch; TYPE_1__* hw; } ;
struct minstrel_mcs_group_data {size_t column; size_t index; int* max_group_tp_rate; struct minstrel_rate_stats* rates; } ;
struct minstrel_ht_sta {scalar_t__ total_packets_cur; scalar_t__ sample_wait; unsigned int sample_group; int* supported; int* max_tp_rate; int max_prob_rate; int /*<<< orphan*/  sample_tries; int /*<<< orphan*/  sample_slow; struct minstrel_mcs_group_data* groups; } ;
struct TYPE_4__ {unsigned int streams; } ;
struct TYPE_3__ {int max_rates; } ;

/* Variables and functions */
 int BIT (int) ; 
 unsigned int MCS_GROUP_RATES ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 scalar_t__ SAMPLE_SWITCH_THR ; 
 unsigned int minstrel_get_duration (int) ; 
 TYPE_2__* minstrel_mcs_groups ; 
 int /*<<< orphan*/  minstrel_set_next_sample_idx (struct minstrel_ht_sta*) ; 
 int** sample_table ; 

__attribute__((used)) static int
minstrel_get_sample_rate(struct minstrel_priv *mp, struct minstrel_ht_sta *mi)
{
	struct minstrel_rate_stats *mrs;
	struct minstrel_mcs_group_data *mg;
	unsigned int sample_dur, sample_group, cur_max_tp_streams;
	int tp_rate1, tp_rate2;
	int sample_idx = 0;

	if (mp->hw->max_rates == 1 && mp->sample_switch &&
	    (mi->total_packets_cur >= SAMPLE_SWITCH_THR ||
	     mp->sample_switch == 1))
		return -1;

	if (mi->sample_wait > 0) {
		mi->sample_wait--;
		return -1;
	}

	if (!mi->sample_tries)
		return -1;

	sample_group = mi->sample_group;
	mg = &mi->groups[sample_group];
	sample_idx = sample_table[mg->column][mg->index];
	minstrel_set_next_sample_idx(mi);

	if (!(mi->supported[sample_group] & BIT(sample_idx)))
		return -1;

	mrs = &mg->rates[sample_idx];
	sample_idx += sample_group * MCS_GROUP_RATES;

	/* Set tp_rate1, tp_rate2 to the highest / second highest max_tp_rate */
	if (minstrel_get_duration(mi->max_tp_rate[0]) >
	    minstrel_get_duration(mi->max_tp_rate[1])) {
		tp_rate1 = mi->max_tp_rate[1];
		tp_rate2 = mi->max_tp_rate[0];
	} else {
		tp_rate1 = mi->max_tp_rate[0];
		tp_rate2 = mi->max_tp_rate[1];
	}

	/*
	 * Sampling might add some overhead (RTS, no aggregation)
	 * to the frame. Hence, don't use sampling for the highest currently
	 * used highest throughput or probability rate.
	 */
	if (sample_idx == mi->max_tp_rate[0] || sample_idx == mi->max_prob_rate)
		return -1;

	/*
	 * Do not sample if the probability is already higher than 95%,
	 * or if the rate is 3 times slower than the current max probability
	 * rate, to avoid wasting airtime.
	 */
	sample_dur = minstrel_get_duration(sample_idx);
	if (mrs->prob_ewma > MINSTREL_FRAC(95, 100) ||
	    minstrel_get_duration(mi->max_prob_rate) * 3 < sample_dur)
		return -1;


	/*
	 * For devices with no configurable multi-rate retry, skip sampling
	 * below the per-group max throughput rate, and only use one sampling
	 * attempt per rate
	 */
	if (mp->hw->max_rates == 1 &&
	    (minstrel_get_duration(mg->max_group_tp_rate[0]) < sample_dur ||
	     mrs->attempts))
		return -1;

	/* Skip already sampled slow rates */
	if (sample_dur >= minstrel_get_duration(tp_rate1) && mrs->attempts)
		return -1;

	/*
	 * Make sure that lower rates get sampled only occasionally,
	 * if the link is working perfectly.
	 */

	cur_max_tp_streams = minstrel_mcs_groups[tp_rate1 /
		MCS_GROUP_RATES].streams;
	if (sample_dur >= minstrel_get_duration(tp_rate2) &&
	    (cur_max_tp_streams - 1 <
	     minstrel_mcs_groups[sample_group].streams ||
	     sample_dur >= minstrel_get_duration(mi->max_prob_rate))) {
		if (mrs->sample_skipped < 20)
			return -1;

		if (mi->sample_slow++ > 2)
			return -1;
	}
	mi->sample_tries--;

	return sample_idx;
}