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
struct objagg_stats {int stats_info_count; TYPE_2__* stats_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  delta_user_count; int /*<<< orphan*/  user_count; } ;
struct TYPE_4__ {scalar_t__ is_root; TYPE_1__ stats; int /*<<< orphan*/  objagg_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  obj_to_key_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __pr_debug_stats(const struct objagg_stats *stats)
{
	int i;

	for (i = 0; i < stats->stats_info_count; i++)
		pr_debug("Stat index %d key %u: u %d, d %d, %s\n", i,
			 obj_to_key_id(stats->stats_info[i].objagg_obj),
			 stats->stats_info[i].stats.user_count,
			 stats->stats_info[i].stats.delta_user_count,
			 stats->stats_info[i].is_root ? "root" : "noroot");
}