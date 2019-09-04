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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ is_swap_pmd (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

spinlock_t *__pmd_trans_huge_lock(pmd_t *pmd, struct vm_area_struct *vma)
{
	spinlock_t *ptl;
	ptl = pmd_lock(vma->vm_mm, pmd);
	if (likely(is_swap_pmd(*pmd) || pmd_trans_huge(*pmd) ||
			pmd_devmap(*pmd)))
		return ptl;
	spin_unlock(ptl);
	return NULL;
}