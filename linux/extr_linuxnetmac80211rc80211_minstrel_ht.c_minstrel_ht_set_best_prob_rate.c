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
struct minstrel_rate_stats {int prob_ewma; } ;
struct minstrel_mcs_group_data {size_t max_group_prob_rate; struct minstrel_rate_stats* rates; } ;
struct minstrel_ht_sta {size_t max_prob_rate; size_t* max_tp_rate; struct minstrel_mcs_group_data* groups; } ;

/* Variables and functions */
 size_t MCS_GROUP_RATES ; 
 size_t MINSTREL_CCK_GROUP ; 
 int MINSTREL_FRAC (int,int) ; 
 int minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,int,int,int) ; 

__attribute__((used)) static void
minstrel_ht_set_best_prob_rate(struct minstrel_ht_sta *mi, u16 index)
{
	struct minstrel_mcs_group_data *mg;
	struct minstrel_rate_stats *mrs;
	int tmp_group, tmp_idx, tmp_tp_avg, tmp_prob;
	int max_tp_group, cur_tp_avg, cur_group, cur_idx;
	int max_gpr_group, max_gpr_idx;
	int max_gpr_tp_avg, max_gpr_prob;

	cur_group = index / MCS_GROUP_RATES;
	cur_idx = index % MCS_GROUP_RATES;
	mg = &mi->groups[index / MCS_GROUP_RATES];
	mrs = &mg->rates[index % MCS_GROUP_RATES];

	tmp_group = mi->max_prob_rate / MCS_GROUP_RATES;
	tmp_idx = mi->max_prob_rate % MCS_GROUP_RATES;
	tmp_prob = mi->groups[tmp_group].rates[tmp_idx].prob_ewma;
	tmp_tp_avg = minstrel_ht_get_tp_avg(mi, tmp_group, tmp_idx, tmp_prob);

	/* if max_tp_rate[0] is from MCS_GROUP max_prob_rate get selected from
	 * MCS_GROUP as well as CCK_GROUP rates do not allow aggregation */
	max_tp_group = mi->max_tp_rate[0] / MCS_GROUP_RATES;
	if((index / MCS_GROUP_RATES == MINSTREL_CCK_GROUP) &&
	    (max_tp_group != MINSTREL_CCK_GROUP))
		return;

	max_gpr_group = mg->max_group_prob_rate / MCS_GROUP_RATES;
	max_gpr_idx = mg->max_group_prob_rate % MCS_GROUP_RATES;
	max_gpr_prob = mi->groups[max_gpr_group].rates[max_gpr_idx].prob_ewma;

	if (mrs->prob_ewma > MINSTREL_FRAC(75, 100)) {
		cur_tp_avg = minstrel_ht_get_tp_avg(mi, cur_group, cur_idx,
						    mrs->prob_ewma);
		if (cur_tp_avg > tmp_tp_avg)
			mi->max_prob_rate = index;

		max_gpr_tp_avg = minstrel_ht_get_tp_avg(mi, max_gpr_group,
							max_gpr_idx,
							max_gpr_prob);
		if (cur_tp_avg > max_gpr_tp_avg)
			mg->max_group_prob_rate = index;
	} else {
		if (mrs->prob_ewma > tmp_prob)
			mi->max_prob_rate = index;
		if (mrs->prob_ewma > max_gpr_prob)
			mg->max_group_prob_rate = index;
	}
}