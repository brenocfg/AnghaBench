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
struct TYPE_4__ {int /*<<< orphan*/  next_prev_tid; int /*<<< orphan*/  next_prev_pid; } ;
struct TYPE_3__ {int misc; scalar_t__ type; } ;
union perf_event {TYPE_2__ context_switch; TYPE_1__ header; } ;
typedef  scalar_t__ u64 ;
struct perf_sample {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct machine {int dummy; } ;
struct db_export {int (* export_context_switch ) (struct db_export*,scalar_t__,struct machine*,struct perf_sample*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ;scalar_t__ context_switch_last_db_id; } ;
struct comm {scalar_t__ db_id; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int PERF_RECORD_MISC_SWITCH_OUT ; 
 int PERF_RECORD_MISC_SWITCH_OUT_PREEMPT ; 
 scalar_t__ PERF_RECORD_SWITCH_CPU_WIDE ; 
 int db_export__machine (struct db_export*,struct machine*) ; 
 int db_export__pid_tid (struct db_export*,struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,struct comm**,int*) ; 
 int stub1 (struct db_export*,scalar_t__,struct machine*,struct perf_sample*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 

int db_export__switch(struct db_export *dbe, union perf_event *event,
		      struct perf_sample *sample, struct machine *machine)
{
	bool out = event->header.misc & PERF_RECORD_MISC_SWITCH_OUT;
	bool out_preempt = out &&
		(event->header.misc & PERF_RECORD_MISC_SWITCH_OUT_PREEMPT);
	int flags = out | (out_preempt << 1);
	bool is_idle_a = false, is_idle_b = false;
	u64 th_a_id = 0, th_b_id = 0;
	u64 comm_out_id, comm_in_id;
	struct comm *comm_a = NULL;
	struct comm *comm_b = NULL;
	u64 th_out_id, th_in_id;
	u64 db_id;
	int err;

	err = db_export__machine(dbe, machine);
	if (err)
		return err;

	err = db_export__pid_tid(dbe, machine, sample->pid, sample->tid,
				 &th_a_id, &comm_a, &is_idle_a);
	if (err)
		return err;

	if (event->header.type == PERF_RECORD_SWITCH_CPU_WIDE) {
		pid_t pid = event->context_switch.next_prev_pid;
		pid_t tid = event->context_switch.next_prev_tid;

		err = db_export__pid_tid(dbe, machine, pid, tid, &th_b_id,
					 &comm_b, &is_idle_b);
		if (err)
			return err;
	}

	/*
	 * Do not export if both threads are unknown (i.e. not being traced),
	 * or one is unknown and the other is the idle task.
	 */
	if ((!th_a_id || is_idle_a) && (!th_b_id || is_idle_b))
		return 0;

	db_id = ++dbe->context_switch_last_db_id;

	if (out) {
		th_out_id   = th_a_id;
		th_in_id    = th_b_id;
		comm_out_id = comm_a ? comm_a->db_id : 0;
		comm_in_id  = comm_b ? comm_b->db_id : 0;
	} else {
		th_out_id   = th_b_id;
		th_in_id    = th_a_id;
		comm_out_id = comm_b ? comm_b->db_id : 0;
		comm_in_id  = comm_a ? comm_a->db_id : 0;
	}

	if (dbe->export_context_switch)
		return dbe->export_context_switch(dbe, db_id, machine, sample,
						  th_out_id, comm_out_id,
						  th_in_id, comm_in_id, flags);
	return 0;
}