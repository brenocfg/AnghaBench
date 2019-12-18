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
struct TYPE_4__ {scalar_t__ type; int exclude_kernel; int exclude_hv; int /*<<< orphan*/  pinned; int /*<<< orphan*/  precise_ip; int /*<<< orphan*/  exclude_user; } ;
struct TYPE_5__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct TYPE_6__ {int nr_entries; } ;
struct evlist {TYPE_3__ core; } ;

/* Variables and functions */
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 

__attribute__((used)) static int test__checkevent_pmu_events(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
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