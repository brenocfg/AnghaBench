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
struct perf_event_attr {int exclude_kernel; scalar_t__ precise_ip; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct evsel {int precise_max; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 scalar_t__ asprintf (int /*<<< orphan*/ *,char*,char*,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  evsel__delete (struct evsel*) ; 
 struct evsel* evsel__new (struct perf_event_attr*) ; 
 int /*<<< orphan*/  perf_event_can_profile_kernel () ; 

struct evsel *perf_evsel__new_cycles(bool precise)
{
	struct perf_event_attr attr = {
		.type	= PERF_TYPE_HARDWARE,
		.config	= PERF_COUNT_HW_CPU_CYCLES,
		.exclude_kernel	= !perf_event_can_profile_kernel(),
	};
	struct evsel *evsel;

	event_attr_init(&attr);

	if (!precise)
		goto new_event;

	/*
	 * Now let the usual logic to set up the perf_event_attr defaults
	 * to kick in when we return and before perf_evsel__open() is called.
	 */
new_event:
	evsel = evsel__new(&attr);
	if (evsel == NULL)
		goto out;

	evsel->precise_max = true;

	/* use asprintf() because free(evsel) assumes name is allocated */
	if (asprintf(&evsel->name, "cycles%s%s%.*s",
		     (attr.precise_ip || attr.exclude_kernel) ? ":" : "",
		     attr.exclude_kernel ? "u" : "",
		     attr.precise_ip ? attr.precise_ip + 1 : 0, "ppp") < 0)
		goto error_free;
out:
	return evsel;
error_free:
	evsel__delete(evsel);
	evsel = NULL;
	goto out;
}