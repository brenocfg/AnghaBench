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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_tool {int dummy; } ;
struct perf_sample {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int perf_event__process_mmap2 (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 
 int /*<<< orphan*/  perf_event__repipe (struct perf_tool*,union perf_event*,struct perf_sample*,struct machine*) ; 

__attribute__((used)) static int perf_event__repipe_mmap2(struct perf_tool *tool,
				   union perf_event *event,
				   struct perf_sample *sample,
				   struct machine *machine)
{
	int err;

	err = perf_event__process_mmap2(tool, event, sample, machine);
	perf_event__repipe(tool, event, sample, machine);

	return err;
}