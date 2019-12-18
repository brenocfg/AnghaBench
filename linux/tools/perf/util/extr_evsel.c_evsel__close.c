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
struct evsel {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evsel__free_id (int /*<<< orphan*/ *) ; 

void evsel__close(struct evsel *evsel)
{
	perf_evsel__close(&evsel->core);
	perf_evsel__free_id(&evsel->core);
}