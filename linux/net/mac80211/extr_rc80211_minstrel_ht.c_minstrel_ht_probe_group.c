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
struct minstrel_ht_sta {int dummy; } ;
struct mcs_group {scalar_t__ bw; int streams; } ;

/* Variables and functions */

__attribute__((used)) static bool
minstrel_ht_probe_group(struct minstrel_ht_sta *mi, const struct mcs_group *tp_group,
						int tp_idx, const struct mcs_group *group)
{
	if (group->bw < tp_group->bw)
		return false;

	if (group->streams == tp_group->streams)
		return true;

	if (tp_idx < 4 && group->streams == tp_group->streams - 1)
		return true;

	return group->streams == tp_group->streams + 1;
}