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
struct perf_evsel {int /*<<< orphan*/  node; } ;
struct perf_evlist {int nr_entries; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_evlist__propagate_maps (struct perf_evlist*,struct perf_evsel*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void perf_evlist__add(struct perf_evlist *evlist,
		      struct perf_evsel *evsel)
{
	list_add_tail(&evsel->node, &evlist->entries);
	evlist->nr_entries += 1;
	__perf_evlist__propagate_maps(evlist, evsel);
}