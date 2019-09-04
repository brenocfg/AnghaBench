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
struct perf_evsel {scalar_t__ system_wide; } ;
struct perf_evlist {int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 int thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evlist__nr_threads(struct perf_evlist *evlist,
				   struct perf_evsel *evsel)
{
	if (evsel->system_wide)
		return 1;
	else
		return thread_map__nr(evlist->threads);
}