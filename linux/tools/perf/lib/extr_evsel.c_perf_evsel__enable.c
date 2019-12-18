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
struct perf_evsel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int perf_evsel__run_ioctl (struct perf_evsel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int perf_evsel__enable(struct perf_evsel *evsel)
{
	return perf_evsel__run_ioctl(evsel, PERF_EVENT_IOC_ENABLE, 0);
}