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
struct TYPE_4__ {scalar_t__ type; scalar_t__ config; scalar_t__ sample_period; scalar_t__ config1; int config2; } ;
struct TYPE_5__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct TYPE_6__ {int nr_entries; } ;
struct evlist {TYPE_3__ core; } ;

/* Variables and functions */
 scalar_t__ PERF_COUNT_HW_CPU_CYCLES ; 
 scalar_t__ PERF_TYPE_HARDWARE ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 

__attribute__((used)) static int test__checkevent_symbolic_name_config(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 1 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_HARDWARE == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",
			PERF_COUNT_HW_CPU_CYCLES == evsel->core.attr.config);
	/*
	 * The period value gets configured within perf_evlist__config,
	 * while this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",
			0 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong config1",
			0 == evsel->core.attr.config1);
	TEST_ASSERT_VAL("wrong config2",
			1 == evsel->core.attr.config2);
	return 0;
}