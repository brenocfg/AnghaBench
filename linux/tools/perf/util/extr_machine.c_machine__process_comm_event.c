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
struct TYPE_3__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {int misc; } ;
union perf_event {TYPE_1__ comm; TYPE_2__ header; } ;
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; } ;
struct machine {int comm_exec; } ;

/* Variables and functions */
 int PERF_RECORD_MISC_COMM_EXEC ; 
 scalar_t__ __thread__set_comm (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_printf (char*) ; 
 scalar_t__ dump_trace ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event__fprintf_comm (union perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

int machine__process_comm_event(struct machine *machine, union perf_event *event,
				struct perf_sample *sample)
{
	struct thread *thread = machine__findnew_thread(machine,
							event->comm.pid,
							event->comm.tid);
	bool exec = event->header.misc & PERF_RECORD_MISC_COMM_EXEC;
	int err = 0;

	if (exec)
		machine->comm_exec = true;

	if (dump_trace)
		perf_event__fprintf_comm(event, stdout);

	if (thread == NULL ||
	    __thread__set_comm(thread, event->comm.comm, sample->time, exec)) {
		dump_printf("problem processing PERF_RECORD_COMM, skipping event.\n");
		err = -1;
	}

	thread__put(thread);

	return err;
}