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
struct TYPE_2__ {int stats_num; int /*<<< orphan*/ * stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  evsel_list ; 
 int /*<<< orphan*/  perf_evlist__reset_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_stat__reset_shadow_per_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_stat__reset_shadow_stats () ; 
 TYPE_1__ stat_config ; 

__attribute__((used)) static void perf_stat__reset_stats(void)
{
	int i;

	perf_evlist__reset_stats(evsel_list);
	perf_stat__reset_shadow_stats();

	for (i = 0; i < stat_config.stats_num; i++)
		perf_stat__reset_shadow_per_stat(&stat_config.stats[i]);
}