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
 int /*<<< orphan*/ * KDB_TSKREGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kdb_current_regs ; 
 struct task_struct* kdb_current_task ; 
 int /*<<< orphan*/  kdb_process_cpu (struct task_struct*) ; 
 scalar_t__ kdb_task_has_cpu (struct task_struct*) ; 

void kdb_set_current_task(struct task_struct *p)
{
	kdb_current_task = p;

	if (kdb_task_has_cpu(p)) {
		kdb_current_regs = KDB_TSKREGS(kdb_process_cpu(p));
		return;
	}
	kdb_current_regs = NULL;
}