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
struct evsel {int idx; int tracking; int /*<<< orphan*/  core; struct evlist* evlist; } ;
struct TYPE_2__ {int nr_entries; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evlist__add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evlist__set_id_pos (struct evlist*) ; 

void evlist__add(struct evlist *evlist, struct evsel *entry)
{
	entry->evlist = evlist;
	entry->idx = evlist->core.nr_entries;
	entry->tracking = !entry->idx;

	perf_evlist__add(&evlist->core, &entry->core);

	if (evlist->core.nr_entries == 1)
		perf_evlist__set_id_pos(evlist);
}