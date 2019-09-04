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
struct TYPE_2__ {int ordered_events; int no_warn; int /*<<< orphan*/  fork; int /*<<< orphan*/  exit; int /*<<< orphan*/  comm; int /*<<< orphan*/  mmap2; int /*<<< orphan*/  mmap; } ;
struct report {TYPE_1__ tool; scalar_t__ mmaps_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_event__process_comm ; 
 int /*<<< orphan*/  perf_event__process_exit ; 
 int /*<<< orphan*/  perf_event__process_fork ; 
 int /*<<< orphan*/  perf_event__process_mmap ; 
 int /*<<< orphan*/  perf_event__process_mmap2 ; 

__attribute__((used)) static void tasks_setup(struct report *rep)
{
	memset(&rep->tool, 0, sizeof(rep->tool));
	rep->tool.ordered_events = true;
	if (rep->mmaps_mode) {
		rep->tool.mmap = perf_event__process_mmap;
		rep->tool.mmap2 = perf_event__process_mmap2;
	}
	rep->tool.comm = perf_event__process_comm;
	rep->tool.exit = perf_event__process_exit;
	rep->tool.fork = perf_event__process_fork;
	rep->tool.no_warn = true;
}