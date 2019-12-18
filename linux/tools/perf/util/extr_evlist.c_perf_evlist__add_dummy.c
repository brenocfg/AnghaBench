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
struct perf_event_attr {int size; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct evsel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;
struct evlist {TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PERF_COUNT_SW_DUMMY ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  evlist__add (struct evlist*,struct evsel*) ; 
 struct evsel* perf_evsel__new_idx (struct perf_event_attr*,int /*<<< orphan*/ ) ; 

int perf_evlist__add_dummy(struct evlist *evlist)
{
	struct perf_event_attr attr = {
		.type	= PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_DUMMY,
		.size	= sizeof(attr), /* to capture ABI version */
	};
	struct evsel *evsel = perf_evsel__new_idx(&attr, evlist->core.nr_entries);

	if (evsel == NULL)
		return -ENOMEM;

	evlist__add(evlist, evsel);
	return 0;
}