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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * map_cmdline_to_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 void* saved_cmdlines_next (struct seq_file*,void*,scalar_t__*) ; 
 TYPE_1__* savedcmd ; 
 int /*<<< orphan*/  trace_cmdline_lock ; 

__attribute__((used)) static void *saved_cmdlines_start(struct seq_file *m, loff_t *pos)
{
	void *v;
	loff_t l = 0;

	preempt_disable();
	arch_spin_lock(&trace_cmdline_lock);

	v = &savedcmd->map_cmdline_to_pid[0];
	while (l <= *pos) {
		v = saved_cmdlines_next(m, v, &l);
		if (!v)
			return NULL;
	}

	return v;
}