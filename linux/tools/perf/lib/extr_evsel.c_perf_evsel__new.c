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
struct perf_event_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__init (struct perf_evsel*,struct perf_event_attr*) ; 
 struct perf_evsel* zalloc (int) ; 

struct perf_evsel *perf_evsel__new(struct perf_event_attr *attr)
{
	struct perf_evsel *evsel = zalloc(sizeof(*evsel));

	if (evsel != NULL)
		perf_evsel__init(evsel, attr);

	return evsel;
}