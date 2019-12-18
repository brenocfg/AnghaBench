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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/ * pgtable_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_inc_nr_ptes (struct mm_struct*) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_populate (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_alloc_one (struct mm_struct*) ; 
 int /*<<< orphan*/  pte_free (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __pte_alloc(struct mm_struct *mm, pmd_t *pmd)
{
	spinlock_t *ptl;
	pgtable_t new = pte_alloc_one(mm);
	if (!new)
		return -ENOMEM;

	/*
	 * Ensure all pte setup (eg. pte page lock and page clearing) are
	 * visible before the pte is made visible to other CPUs by being
	 * put into page tables.
	 *
	 * The other side of the story is the pointer chasing in the page
	 * table walking code (when walking the page table without locking;
	 * ie. most of the time). Fortunately, these data accesses consist
	 * of a chain of data-dependent loads, meaning most CPUs (alpha
	 * being the notable exception) will already guarantee loads are
	 * seen in-order. See the alpha page table accessors for the
	 * smp_read_barrier_depends() barriers in page table walking code.
	 */
	smp_wmb(); /* Could be smp_wmb__xxx(before|after)_spin_lock */

	ptl = pmd_lock(mm, pmd);
	if (likely(pmd_none(*pmd))) {	/* Has another populated it ? */
		mm_inc_nr_ptes(mm);
		pmd_populate(mm, pmd, new);
		new = NULL;
	}
	spin_unlock(ptl);
	if (new)
		pte_free(mm, new);
	return 0;
}