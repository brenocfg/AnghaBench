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
struct mmu_notifier_range {scalar_t__ event; TYPE_1__* vma; } ;
struct TYPE_2__ {int vm_flags; } ;

/* Variables and functions */
 scalar_t__ MMU_NOTIFY_PROTECTION_VMA ; 
 int VM_READ ; 

bool
mmu_notifier_range_update_to_read_only(const struct mmu_notifier_range *range)
{
	if (!range->vma || range->event != MMU_NOTIFY_PROTECTION_VMA)
		return false;
	/* Return true if the vma still have the read flag set. */
	return range->vma->vm_flags & VM_READ;
}