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
struct perf_thread_map {int dummy; } ;
struct perf_evsel {struct perf_thread_map* threads; } ;

/* Variables and functions */

struct perf_thread_map *perf_evsel__threads(struct perf_evsel *evsel)
{
	return evsel->threads;
}