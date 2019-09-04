#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
union perf_event {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_event__sample_event_size (struct perf_sample*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int perf_event__synthesize_sample (union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_sample*) ; 

__attribute__((used)) static int intel_pt_inject_event(union perf_event *event,
				 struct perf_sample *sample, u64 type)
{
	event->header.size = perf_event__sample_event_size(sample, type, 0);
	return perf_event__synthesize_sample(event, type, 0, sample);
}