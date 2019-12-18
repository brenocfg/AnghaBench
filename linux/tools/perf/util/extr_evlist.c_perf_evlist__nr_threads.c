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
struct TYPE_3__ {scalar_t__ system_wide; } ;
struct evsel {TYPE_1__ core; } ;
struct TYPE_4__ {int /*<<< orphan*/  threads; } ;
struct evlist {TYPE_2__ core; } ;

/* Variables and functions */
 int perf_thread_map__nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evlist__nr_threads(struct evlist *evlist,
				   struct evsel *evsel)
{
	if (evsel->core.system_wide)
		return 1;
	else
		return perf_thread_map__nr(evlist->core.threads);
}