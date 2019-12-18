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
typedef  int u16 ;
struct minstrel_ht_sta {TYPE_2__* groups; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct TYPE_3__ {int prob_ewma; } ;

/* Variables and functions */
 int MAX_THR_RATES ; 
 int MCS_GROUP_RATES ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,int,int,int) ; 

__attribute__((used)) static void
minstrel_ht_sort_best_tp_rates(struct minstrel_ht_sta *mi, u16 index,
			       u16 *tp_list)
{
	int cur_group, cur_idx, cur_tp_avg, cur_prob;
	int tmp_group, tmp_idx, tmp_tp_avg, tmp_prob;
	int j = MAX_THR_RATES;

	cur_group = index / MCS_GROUP_RATES;
	cur_idx = index  % MCS_GROUP_RATES;
	cur_prob = mi->groups[cur_group].rates[cur_idx].prob_ewma;
	cur_tp_avg = minstrel_ht_get_tp_avg(mi, cur_group, cur_idx, cur_prob);

	do {
		tmp_group = tp_list[j - 1] / MCS_GROUP_RATES;
		tmp_idx = tp_list[j - 1] % MCS_GROUP_RATES;
		tmp_prob = mi->groups[tmp_group].rates[tmp_idx].prob_ewma;
		tmp_tp_avg = minstrel_ht_get_tp_avg(mi, tmp_group, tmp_idx,
						    tmp_prob);
		if (cur_tp_avg < tmp_tp_avg ||
		    (cur_tp_avg == tmp_tp_avg && cur_prob <= tmp_prob))
			break;
		j--;
	} while (j > 0);

	if (j < MAX_THR_RATES - 1) {
		memmove(&tp_list[j + 1], &tp_list[j], (sizeof(*tp_list) *
		       (MAX_THR_RATES - (j + 1))));
	}
	if (j < MAX_THR_RATES)
		tp_list[j] = index;
}