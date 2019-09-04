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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int EEXIST ; 
 int EFAULT ; 
 unsigned int FOLL_GET ; 
 unsigned int FOLL_TOUCH ; 
 unsigned int FOLL_WRITE ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mmu_cache (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int follow_pfn_pte(struct vm_area_struct *vma, unsigned long address,
		pte_t *pte, unsigned int flags)
{
	/* No page to get reference */
	if (flags & FOLL_GET)
		return -EFAULT;

	if (flags & FOLL_TOUCH) {
		pte_t entry = *pte;

		if (flags & FOLL_WRITE)
			entry = pte_mkdirty(entry);
		entry = pte_mkyoung(entry);

		if (!pte_same(*pte, entry)) {
			set_pte_at(vma->vm_mm, address, pte, entry);
			update_mmu_cache(vma, address, pte);
		}
	}

	/* Proper page table entry exists, but no corresponding struct page */
	return -EEXIST;
}