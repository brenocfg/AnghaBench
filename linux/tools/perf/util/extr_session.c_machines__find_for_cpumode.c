#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {scalar_t__ type; } ;
union perf_event {TYPE_1__ mmap; TYPE_2__ header; } ;
typedef  int /*<<< orphan*/  u32 ;
struct perf_sample {scalar_t__ cpumode; int /*<<< orphan*/  pid; } ;
struct machine {int dummy; } ;
struct machines {struct machine host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GUEST_KERNEL_ID ; 
 scalar_t__ PERF_RECORD_MISC_GUEST_KERNEL ; 
 scalar_t__ PERF_RECORD_MISC_GUEST_USER ; 
 scalar_t__ PERF_RECORD_MMAP ; 
 scalar_t__ PERF_RECORD_MMAP2 ; 
 struct machine* machines__find (struct machines*,int /*<<< orphan*/ ) ; 
 struct machine* machines__findnew (struct machines*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_guest ; 

__attribute__((used)) static struct machine *machines__find_for_cpumode(struct machines *machines,
					       union perf_event *event,
					       struct perf_sample *sample)
{
	struct machine *machine;

	if (perf_guest &&
	    ((sample->cpumode == PERF_RECORD_MISC_GUEST_KERNEL) ||
	     (sample->cpumode == PERF_RECORD_MISC_GUEST_USER))) {
		u32 pid;

		if (event->header.type == PERF_RECORD_MMAP
		    || event->header.type == PERF_RECORD_MMAP2)
			pid = event->mmap.pid;
		else
			pid = sample->pid;

		machine = machines__find(machines, pid);
		if (!machine)
			machine = machines__findnew(machines, DEFAULT_GUEST_KERNEL_ID);
		return machine;
	}

	return &machines->host;
}