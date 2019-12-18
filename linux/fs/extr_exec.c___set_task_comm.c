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
struct task_struct {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_event_comm (struct task_struct*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  trace_task_rename (struct task_struct*,char const*) ; 

void __set_task_comm(struct task_struct *tsk, const char *buf, bool exec)
{
	task_lock(tsk);
	trace_task_rename(tsk, buf);
	strlcpy(tsk->comm, buf, sizeof(tsk->comm));
	task_unlock(tsk);
	perf_event_comm(tsk, exec);
}