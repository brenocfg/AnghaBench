#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ delta_user_count; int user_count; } ;
struct objagg_obj_stats_info {scalar_t__ is_root; TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static int objagg_stats_info_sort_cmp_func(const void *a, const void *b)
{
	const struct objagg_obj_stats_info *stats_info1 = a;
	const struct objagg_obj_stats_info *stats_info2 = b;

	if (stats_info1->is_root != stats_info2->is_root)
		return stats_info2->is_root - stats_info1->is_root;
	if (stats_info1->stats.delta_user_count !=
	    stats_info2->stats.delta_user_count)
		return stats_info2->stats.delta_user_count -
		       stats_info1->stats.delta_user_count;
	return stats_info2->stats.user_count - stats_info1->stats.user_count;
}