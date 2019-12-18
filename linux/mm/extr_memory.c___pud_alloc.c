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
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mm_inc_nr_puds (struct mm_struct*) ; 
 int /*<<< orphan*/  p4d_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_alloc_one (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pud_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __pud_alloc(struct mm_struct *mm, p4d_t *p4d, unsigned long address)
{
	pud_t *new = pud_alloc_one(mm, address);
	if (!new)
		return -ENOMEM;

	smp_wmb(); /* See comment in __pte_alloc */

	spin_lock(&mm->page_table_lock);
#ifndef __ARCH_HAS_5LEVEL_HACK
	if (!p4d_present(*p4d)) {
		mm_inc_nr_puds(mm);
		p4d_populate(mm, p4d, new);
	} else	/* Another has populated it */
		pud_free(mm, new);
#else
	if (!pgd_present(*p4d)) {
		mm_inc_nr_puds(mm);
		pgd_populate(mm, p4d, new);
	} else	/* Another has populated it */
		pud_free(mm, new);
#endif /* __ARCH_HAS_5LEVEL_HACK */
	spin_unlock(&mm->page_table_lock);
	return 0;
}