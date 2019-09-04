#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct minstrel_mcs_group_data {size_t max_group_prob_rate; TYPE_1__* rates; } ;
struct minstrel_ht_sta {size_t* max_tp_rate; size_t max_prob_rate; struct minstrel_mcs_group_data* groups; int /*<<< orphan*/ * supported; } ;
struct TYPE_5__ {int streams; } ;
struct TYPE_4__ {int prob_ewma; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 size_t MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 int minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,int,int,int) ; 
 TYPE_2__* minstrel_mcs_groups ; 

__attribute__((used)) static inline void
minstrel_ht_prob_rate_reduce_streams(struct minstrel_ht_sta *mi)
{
	struct minstrel_mcs_group_data *mg;
	int tmp_max_streams, group, tmp_idx, tmp_prob;
	int tmp_tp = 0;

	tmp_max_streams = minstrel_mcs_groups[mi->max_tp_rate[0] /
			  MCS_GROUP_RATES].streams;
	for (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) {
		mg = &mi->groups[group];
		if (!mi->supported[group] || group == MINSTREL_CCK_GROUP)
			continue;

		tmp_idx = mg->max_group_prob_rate % MCS_GROUP_RATES;
		tmp_prob = mi->groups[group].rates[tmp_idx].prob_ewma;

		if (tmp_tp < minstrel_ht_get_tp_avg(mi, group, tmp_idx, tmp_prob) &&
		   (minstrel_mcs_groups[group].streams < tmp_max_streams)) {
				mi->max_prob_rate = mg->max_group_prob_rate;
				tmp_tp = minstrel_ht_get_tp_avg(mi, group,
								tmp_idx,
								tmp_prob);
		}
	}
}