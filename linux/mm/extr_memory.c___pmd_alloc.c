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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mm_inc_nr_pmds (struct mm_struct*) ; 
 int /*<<< orphan*/  pgd_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_alloc_one (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pmd_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address)
{
	spinlock_t *ptl;
	pmd_t *new = pmd_alloc_one(mm, address);
	if (!new)
		return -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	ptl = pud_lock(mm, pud);
#ifndef __ARCH_HAS_4LEVEL_HACK
	if (!pud_present(*pud)) {
		mm_inc_nr_pmds(mm);
		pud_populate(mm, pud, new);
	} else	/* Another has populated it */
		pmd_free(mm, new);
#else
	if (!pgd_present(*pud)) {
		mm_inc_nr_pmds(mm);
		pgd_populate(mm, pud, new);
	} else /* Another has populated it */
		pmd_free(mm, new);
#endif /* __ARCH_HAS_4LEVEL_HACK */
	spin_unlock(ptl);
	return 0;
}