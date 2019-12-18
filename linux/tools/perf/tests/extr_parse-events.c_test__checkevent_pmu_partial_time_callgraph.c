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
struct TYPE_5__ {scalar_t__ type; int config; scalar_t__ sample_period; int sample_type; } ;
struct TYPE_6__ {TYPE_2__ attr; } ;
struct evsel {TYPE_3__ core; } ;
struct TYPE_4__ {int nr_entries; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 int PERF_SAMPLE_TIME ; 
 scalar_t__ PERF_TYPE_RAW ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 int /*<<< orphan*/  evsel__has_callchain (struct evsel*) ; 
 struct evsel* perf_evsel__next (struct evsel*) ; 

__attribute__((used)) static int test__checkevent_pmu_partial_time_callgraph(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	/* cpu/config=1,call-graph=fp,time,period=100000/ */
	TEST_ASSERT_VAL("wrong number of entries", 2 == evlist->core.nr_entries);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",  1 == evsel->core.attr.config);
	/*
	 * The period, time and callgraph value gets configured
	 * within perf_evlist__config,
	 * while this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong callgraph",  !evsel__has_callchain(evsel));
	TEST_ASSERT_VAL("wrong time",  !(PERF_SAMPLE_TIME & evsel->core.attr.sample_type));

	/* cpu/config=2,call-graph=no,time=0,period=2000/ */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config",  2 == evsel->core.attr.config);
	/*
	 * The period, time and callgraph value gets configured
	 * within perf_evlist__config,
	 * while this test executes only parse events method.
	 */
	TEST_ASSERT_VAL("wrong period",     0 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong callgraph",  !evsel__has_callchain(evsel));
	TEST_ASSERT_VAL("wrong time",  !(PERF_SAMPLE_TIME & evsel->core.attr.sample_type));

	return 0;
}