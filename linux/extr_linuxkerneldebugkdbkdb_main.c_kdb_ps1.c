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
struct task_struct {int /*<<< orphan*/  comm; int /*<<< orphan*/  thread; TYPE_1__* parent; int /*<<< orphan*/  pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 struct task_struct const* KDB_TSK (int) ; 
 struct task_struct const* kdb_curr_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_printf (char*,...) ; 
 int kdb_process_cpu (struct task_struct const*) ; 
 scalar_t__ kdb_task_has_cpu (struct task_struct const*) ; 
 int /*<<< orphan*/  kdb_task_state_char (struct task_struct const*) ; 
 scalar_t__ probe_kernel_read (unsigned long*,char*,int) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

void kdb_ps1(const struct task_struct *p)
{
	int cpu;
	unsigned long tmp;

	if (!p || probe_kernel_read(&tmp, (char *)p, sizeof(unsigned long)))
		return;

	cpu = kdb_process_cpu(p);
	kdb_printf("0x%px %8d %8d  %d %4d   %c  0x%px %c%s\n",
		   (void *)p, p->pid, p->parent->pid,
		   kdb_task_has_cpu(p), kdb_process_cpu(p),
		   kdb_task_state_char(p),
		   (void *)(&p->thread),
		   p == kdb_curr_task(raw_smp_processor_id()) ? '*' : ' ',
		   p->comm);
	if (kdb_task_has_cpu(p)) {
		if (!KDB_TSK(cpu)) {
			kdb_printf("  Error: no saved data for this cpu\n");
		} else {
			if (KDB_TSK(cpu) != p)
				kdb_printf("  Error: does not match running "
				   "process table (0x%px)\n", KDB_TSK(cpu));
		}
	}
}