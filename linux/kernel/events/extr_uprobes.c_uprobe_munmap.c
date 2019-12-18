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
struct vm_area_struct {TYPE_1__* vm_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  mm_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_HAS_UPROBES ; 
 int /*<<< orphan*/  MMF_RECALC_UPROBES ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ no_uprobe_events () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valid_vma (struct vm_area_struct*,int) ; 
 scalar_t__ vma_has_uprobes (struct vm_area_struct*,unsigned long,unsigned long) ; 

void uprobe_munmap(struct vm_area_struct *vma, unsigned long start, unsigned long end)
{
	if (no_uprobe_events() || !valid_vma(vma, false))
		return;

	if (!atomic_read(&vma->vm_mm->mm_users)) /* called by mmput() ? */
		return;

	if (!test_bit(MMF_HAS_UPROBES, &vma->vm_mm->flags) ||
	     test_bit(MMF_RECALC_UPROBES, &vma->vm_mm->flags))
		return;

	if (vma_has_uprobes(vma, start, end))
		set_bit(MMF_RECALC_UPROBES, &vma->vm_mm->flags);
}