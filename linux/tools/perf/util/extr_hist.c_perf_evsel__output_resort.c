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
struct ui_progress {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 void perf_evsel__output_resort_cb (struct evsel*,struct ui_progress*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void perf_evsel__output_resort(struct evsel *evsel, struct ui_progress *prog)
{
	return perf_evsel__output_resort_cb(evsel, prog, NULL, NULL);
}