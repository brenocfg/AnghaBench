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
typedef  int /*<<< orphan*/  vm_flags_t ;
struct mm_struct {long total_vm; long exec_vm; long stack_vm; long data_vm; } ;

/* Variables and functions */
 scalar_t__ is_data_mapping (int /*<<< orphan*/ ) ; 
 scalar_t__ is_exec_mapping (int /*<<< orphan*/ ) ; 
 scalar_t__ is_stack_mapping (int /*<<< orphan*/ ) ; 

void vm_stat_account(struct mm_struct *mm, vm_flags_t flags, long npages)
{
	mm->total_vm += npages;

	if (is_exec_mapping(flags))
		mm->exec_vm += npages;
	else if (is_stack_mapping(flags))
		mm->stack_vm += npages;
	else if (is_data_mapping(flags))
		mm->data_vm += npages;
}