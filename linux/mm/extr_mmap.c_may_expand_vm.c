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
typedef  int /*<<< orphan*/  vm_flags_t ;
struct mm_struct {scalar_t__ total_vm; unsigned long data_vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_AS ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 TYPE_1__* current ; 
 scalar_t__ ignore_rlimit_data ; 
 scalar_t__ is_data_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,scalar_t__,char*) ; 
 scalar_t__ rlimit (int /*<<< orphan*/ ) ; 
 unsigned long rlimit_max (int /*<<< orphan*/ ) ; 

bool may_expand_vm(struct mm_struct *mm, vm_flags_t flags, unsigned long npages)
{
	if (mm->total_vm + npages > rlimit(RLIMIT_AS) >> PAGE_SHIFT)
		return false;

	if (is_data_mapping(flags) &&
	    mm->data_vm + npages > rlimit(RLIMIT_DATA) >> PAGE_SHIFT) {
		/* Workaround for Valgrind */
		if (rlimit(RLIMIT_DATA) == 0 &&
		    mm->data_vm + npages <= rlimit_max(RLIMIT_DATA) >> PAGE_SHIFT)
			return true;

		pr_warn_once("%s (%d): VmData %lu exceed data ulimit %lu. Update limits%s.\n",
			     current->comm, current->pid,
			     (mm->data_vm + npages) << PAGE_SHIFT,
			     rlimit(RLIMIT_DATA),
			     ignore_rlimit_data ? "" : " or use boot option ignore_rlimit_data");

		if (!ignore_rlimit_data)
			return false;
	}

	return true;
}