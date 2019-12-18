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
struct perf_stat_evsel {int id; } ;
struct evsel {struct perf_stat_evsel* stats; } ;

/* Variables and functions */
 int PERF_STAT_EVSEL_ID__MAX ; 
 int /*<<< orphan*/ * id_str ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_stat_evsel_id_init(struct evsel *evsel)
{
	struct perf_stat_evsel *ps = evsel->stats;
	int i;

	/* ps->id is 0 hence PERF_STAT_EVSEL_ID__NONE by default */

	for (i = 0; i < PERF_STAT_EVSEL_ID__MAX; i++) {
		if (!strcmp(perf_evsel__name(evsel), id_str[i])) {
			ps->id = i;
			break;
		}
	}
}