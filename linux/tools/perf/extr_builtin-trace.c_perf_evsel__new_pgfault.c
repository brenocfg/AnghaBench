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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event_attr {int mmap_data; int sample_period; int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
struct evsel {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 struct evsel* evsel__new (struct perf_event_attr*) ; 
 int /*<<< orphan*/  trace__pgfault ; 

__attribute__((used)) static struct evsel *perf_evsel__new_pgfault(u64 config)
{
	struct evsel *evsel;
	struct perf_event_attr attr = {
		.type = PERF_TYPE_SOFTWARE,
		.mmap_data = 1,
	};

	attr.config = config;
	attr.sample_period = 1;

	event_attr_init(&attr);

	evsel = evsel__new(&attr);
	if (evsel)
		evsel->handler = trace__pgfault;

	return evsel;
}