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
struct TYPE_2__ {int nr_entries; int /*<<< orphan*/  entries; } ;
struct evlist {int nr_groups; TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_evlist__set_leader (int /*<<< orphan*/ *) ; 

void perf_evlist__set_leader(struct evlist *evlist)
{
	if (evlist->core.nr_entries) {
		evlist->nr_groups = evlist->core.nr_entries > 1 ? 1 : 0;
		__perf_evlist__set_leader(&evlist->core.entries);
	}
}