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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int TRACE_RECORD_CMDLINE ; 
 int TRACE_RECORD_TGID ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ trace_save_cmdline (struct task_struct*) ; 
 scalar_t__ trace_save_tgid (struct task_struct*) ; 
 int /*<<< orphan*/  trace_taskinfo_save ; 
 scalar_t__ tracing_record_taskinfo_skip (int) ; 

void tracing_record_taskinfo_sched_switch(struct task_struct *prev,
					  struct task_struct *next, int flags)
{
	bool done;

	if (tracing_record_taskinfo_skip(flags))
		return;

	/*
	 * Record as much task information as possible. If some fail, continue
	 * to try to record the others.
	 */
	done  = !(flags & TRACE_RECORD_CMDLINE) || trace_save_cmdline(prev);
	done &= !(flags & TRACE_RECORD_CMDLINE) || trace_save_cmdline(next);
	done &= !(flags & TRACE_RECORD_TGID) || trace_save_tgid(prev);
	done &= !(flags & TRACE_RECORD_TGID) || trace_save_tgid(next);

	/* If recording any information failed, retry again soon. */
	if (!done)
		return;

	__this_cpu_write(trace_taskinfo_save, false);
}