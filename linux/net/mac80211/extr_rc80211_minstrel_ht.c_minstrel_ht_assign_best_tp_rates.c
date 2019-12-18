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
typedef  unsigned int u16 ;
struct minstrel_ht_sta {TYPE_2__* groups; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct TYPE_3__ {unsigned int prob_ewma; } ;

/* Variables and functions */
 int MAX_THR_RATES ; 
 unsigned int MCS_GROUP_RATES ; 
 unsigned int minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  minstrel_ht_sort_best_tp_rates (struct minstrel_ht_sta*,unsigned int,unsigned int*) ; 

__attribute__((used)) static void
minstrel_ht_assign_best_tp_rates(struct minstrel_ht_sta *mi,
				 u16 tmp_mcs_tp_rate[MAX_THR_RATES],
				 u16 tmp_cck_tp_rate[MAX_THR_RATES])
{
	unsigned int tmp_group, tmp_idx, tmp_cck_tp, tmp_mcs_tp, tmp_prob;
	int i;

	tmp_group = tmp_cck_tp_rate[0] / MCS_GROUP_RATES;
	tmp_idx = tmp_cck_tp_rate[0] % MCS_GROUP_RATES;
	tmp_prob = mi->groups[tmp_group].rates[tmp_idx].prob_ewma;
	tmp_cck_tp = minstrel_ht_get_tp_avg(mi, tmp_group, tmp_idx, tmp_prob);

	tmp_group = tmp_mcs_tp_rate[0] / MCS_GROUP_RATES;
	tmp_idx = tmp_mcs_tp_rate[0] % MCS_GROUP_RATES;
	tmp_prob = mi->groups[tmp_group].rates[tmp_idx].prob_ewma;
	tmp_mcs_tp = minstrel_ht_get_tp_avg(mi, tmp_group, tmp_idx, tmp_prob);

	if (tmp_cck_tp_rate && tmp_cck_tp > tmp_mcs_tp) {
		for(i = 0; i < MAX_THR_RATES; i++) {
			minstrel_ht_sort_best_tp_rates(mi, tmp_cck_tp_rate[i],
						       tmp_mcs_tp_rate);
		}
	}

}