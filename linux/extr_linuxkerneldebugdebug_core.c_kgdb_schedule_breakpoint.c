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

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdb_active ; 
 int /*<<< orphan*/  kgdb_break_tasklet_var ; 
 int /*<<< orphan*/  kgdb_setting_breakpoint ; 
 int /*<<< orphan*/  kgdb_tasklet_breakpoint ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void kgdb_schedule_breakpoint(void)
{
	if (atomic_read(&kgdb_break_tasklet_var) ||
		atomic_read(&kgdb_active) != -1 ||
		atomic_read(&kgdb_setting_breakpoint))
		return;
	atomic_inc(&kgdb_break_tasklet_var);
	tasklet_schedule(&kgdb_tasklet_breakpoint);
}