#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int exclude_kernel; int exclude_hv; scalar_t__ type; int /*<<< orphan*/  pinned; int /*<<< orphan*/  precise_ip; int /*<<< orphan*/  exclude_user; } ;
struct TYPE_6__ {TYPE_2__ attr; } ;
struct evsel {TYPE_3__ core; } ;
struct TYPE_4__ {int nr_entries; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 struct evsel* perf_evsel__next (struct evsel*) ; 

__attribute__((used)) static int test__checkevent_pmu_events_mix(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	/* pmu-event:u */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);

	/* cpu/pmu-event/u*/
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong exclude_user",
			!evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel",
			evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong pinned", !evsel->core.attr.pinned);

	return 0;
}