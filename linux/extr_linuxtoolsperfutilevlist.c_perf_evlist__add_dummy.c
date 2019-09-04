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
struct perf_evsel {int dummy; } ;
struct perf_evlist {int /*<<< orphan*/  nr_entries; } ;
struct perf_event_attr {int size; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_COUNT_SW_DUMMY ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  perf_evlist__add (struct perf_evlist*,struct perf_evsel*) ; 
 struct perf_evsel* perf_evsel__new_idx (struct perf_event_attr*,int /*<<< orphan*/ ) ; 

int perf_evlist__add_dummy(struct perf_evlist *evlist)
{
	struct perf_event_attr attr = {
		.type	= PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_DUMMY,
		.size	= sizeof(attr), /* to capture ABI version */
	};
	struct perf_evsel *evsel = perf_evsel__new_idx(&attr, evlist->nr_entries);

	if (evsel == NULL)
		return -ENOMEM;

	perf_evlist__add(evlist, evsel);
	return 0;
}