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
struct evsel {int disabled; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int perf_evsel__disable (int /*<<< orphan*/ *) ; 

int evsel__disable(struct evsel *evsel)
{
	int err = perf_evsel__disable(&evsel->core);
	/*
	 * We mark it disabled here so that tools that disable a event can
	 * ignore events after they disable it. I.e. the ring buffer may have
	 * already a few more events queued up before the kernel got the stop
	 * request.
	 */
	if (!err)
		evsel->disabled = true;

	return err;
}