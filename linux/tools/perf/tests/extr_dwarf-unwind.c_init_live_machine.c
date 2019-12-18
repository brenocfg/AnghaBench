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
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  mmap_handler ; 
 int perf_event__synthesize_mmap_events (int /*<<< orphan*/ *,union perf_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct machine*,int) ; 

__attribute__((used)) static int init_live_machine(struct machine *machine)
{
	union perf_event event;
	pid_t pid = getpid();

	return perf_event__synthesize_mmap_events(NULL, &event, pid, pid,
						  mmap_handler, machine, true);
}