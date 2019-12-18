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
struct minstrel_ht_sta {TYPE_1__* groups; int /*<<< orphan*/ * supported; } ;
struct TYPE_4__ {scalar_t__ streams; } ;
struct TYPE_3__ {int* max_group_tp_rate; } ;

/* Variables and functions */
 int MCS_GROUP_RATES ; 
 TYPE_2__* minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_downgrade_rate(struct minstrel_ht_sta *mi, u16 *idx, bool primary)
{
	int group, orig_group;

	orig_group = group = *idx / MCS_GROUP_RATES;
	while (group > 0) {
		group--;

		if (!mi->supported[group])
			continue;

		if (minstrel_mcs_groups[group].streams >
		    minstrel_mcs_groups[orig_group].streams)
			continue;

		if (primary)
			*idx = mi->groups[group].max_group_tp_rate[0];
		else
			*idx = mi->groups[group].max_group_tp_rate[1];
		break;
	}
}