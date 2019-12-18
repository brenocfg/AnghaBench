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
struct minstrel_ht_sta {size_t* max_tp_rate; int* supported; } ;
struct mcs_group {int* duration; int shift; } ;

/* Variables and functions */
 size_t MCS_GROUP_RATES ; 
 int MINSTREL_GROUPS_NB ; 
 int minstrel_get_duration (size_t) ; 
 int /*<<< orphan*/  minstrel_ht_probe_group (struct minstrel_ht_sta*,struct mcs_group const*,int,struct mcs_group const*) ; 
 struct mcs_group* minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_ht_find_probe_rates(struct minstrel_ht_sta *mi, u16 *rates, int *n_rates,
			     bool faster_rate)
{
	const struct mcs_group *group, *tp_group;
	int i, g, max_dur;
	int tp_idx;

	tp_group = &minstrel_mcs_groups[mi->max_tp_rate[0] / MCS_GROUP_RATES];
	tp_idx = mi->max_tp_rate[0] % MCS_GROUP_RATES;

	max_dur = minstrel_get_duration(mi->max_tp_rate[0]);
	if (faster_rate)
		max_dur -= max_dur / 16;

	for (g = 0; g < MINSTREL_GROUPS_NB; g++) {
		u16 supported = mi->supported[g];

		if (!supported)
			continue;

		group = &minstrel_mcs_groups[g];
		if (!minstrel_ht_probe_group(mi, tp_group, tp_idx, group))
			continue;

		for (i = 0; supported; supported >>= 1, i++) {
			int idx;

			if (!(supported & 1))
				continue;

			if ((group->duration[i] << group->shift) > max_dur)
				continue;

			idx = g * MCS_GROUP_RATES + i;
			if (idx == mi->max_tp_rate[0])
				continue;

			rates[(*n_rates)++] = idx;
			break;
		}
	}
}