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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 scalar_t__ vma_is_anonymous (struct vm_area_struct*) ; 

__attribute__((used)) static inline int pmd_move_must_withdraw(spinlock_t *new_pmd_ptl,
					 spinlock_t *old_pmd_ptl,
					 struct vm_area_struct *vma)
{
	/*
	 * With split pmd lock we also need to move preallocated
	 * PTE page table if new_pmd is on different PMD page table.
	 *
	 * We also don't deposit and withdraw tables for file pages.
	 */
	return (new_pmd_ptl != old_pmd_ptl) && vma_is_anonymous(vma);
}