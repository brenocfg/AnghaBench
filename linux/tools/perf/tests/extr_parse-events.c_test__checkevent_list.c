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
struct TYPE_5__ {int type; int config; scalar_t__ config1; scalar_t__ config2; int exclude_user; int exclude_kernel; int exclude_hv; int precise_ip; scalar_t__ sample_type; int sample_period; } ;
struct TYPE_6__ {TYPE_2__ attr; } ;
struct evsel {TYPE_3__ core; } ;
struct TYPE_4__ {int nr_entries; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 scalar_t__ PERF_TP_SAMPLE_TYPE ; 
 int PERF_TYPE_RAW ; 
 int PERF_TYPE_TRACEPOINT ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 struct evsel* perf_evsel__next (struct evsel*) ; 

__attribute__((used)) static int test__checkevent_list(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong number of entries", 3 == evlist->core.nr_entries);

	/* r1 */
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_RAW == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 1 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong config1", 0 == evsel->core.attr.config1);
	TEST_ASSERT_VAL("wrong config2", 0 == evsel->core.attr.config2);
	TEST_ASSERT_VAL("wrong exclude_user", !evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	/* syscalls:sys_enter_openat:k */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", PERF_TYPE_TRACEPOINT == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong sample_type",
		PERF_TP_SAMPLE_TYPE == evsel->core.attr.sample_type);
	TEST_ASSERT_VAL("wrong sample_period", 1 == evsel->core.attr.sample_period);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", !evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", !evsel->core.attr.precise_ip);

	/* 1:1:hp */
	evsel = perf_evsel__next(evsel);
	TEST_ASSERT_VAL("wrong type", 1 == evsel->core.attr.type);
	TEST_ASSERT_VAL("wrong config", 1 == evsel->core.attr.config);
	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);

	return 0;
}