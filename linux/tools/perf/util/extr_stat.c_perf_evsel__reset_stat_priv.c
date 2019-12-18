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
struct perf_stat_evsel {int /*<<< orphan*/ * res_stats; } ;
struct evsel {struct perf_stat_evsel* stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_stat_evsel_id_init (struct evsel*) ; 

__attribute__((used)) static void perf_evsel__reset_stat_priv(struct evsel *evsel)
{
	int i;
	struct perf_stat_evsel *ps = evsel->stats;

	for (i = 0; i < 3; i++)
		init_stats(&ps->res_stats[i]);

	perf_stat_evsel_id_init(evsel);
}