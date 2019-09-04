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
 int RECORD_CMDLINE ; 
 int RECORD_TGID ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  sched_cmdline_ref ; 
 int /*<<< orphan*/  sched_tgid_ref ; 
 int /*<<< orphan*/  tracing_record_taskinfo (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
probe_sched_wakeup(void *ignore, struct task_struct *wakee)
{
	int flags;

	flags = (RECORD_TGID * !!sched_tgid_ref) +
		(RECORD_CMDLINE * !!sched_cmdline_ref);

	if (!flags)
		return;
	tracing_record_taskinfo(current, flags);
}