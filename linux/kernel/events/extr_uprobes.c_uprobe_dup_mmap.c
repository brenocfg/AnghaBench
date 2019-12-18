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
struct mm_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_HAS_UPROBES ; 
 int /*<<< orphan*/  MMF_RECALC_UPROBES ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void uprobe_dup_mmap(struct mm_struct *oldmm, struct mm_struct *newmm)
{
	if (test_bit(MMF_HAS_UPROBES, &oldmm->flags)) {
		set_bit(MMF_HAS_UPROBES, &newmm->flags);
		/* unconditionally, dup_mmap() skips VM_DONTCOPY vmas */
		set_bit(MMF_RECALC_UPROBES, &newmm->flags);
	}
}