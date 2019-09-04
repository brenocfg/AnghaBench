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
 int /*<<< orphan*/  irq_work_run_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lazy_list ; 
 int /*<<< orphan*/  raised_list ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void irq_work_run(void)
{
	irq_work_run_list(this_cpu_ptr(&raised_list));
	irq_work_run_list(this_cpu_ptr(&lazy_list));
}