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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int dummy; } ;
struct mm_walk {unsigned char* private; int /*<<< orphan*/  mm; struct vm_area_struct* vma; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __mincore_unmapped_range (unsigned long,unsigned long,struct vm_area_struct*,unsigned char*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 unsigned char mincore_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ non_swap_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_trans_huge_lock (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mincore_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end,
			struct mm_walk *walk)
{
	spinlock_t *ptl;
	struct vm_area_struct *vma = walk->vma;
	pte_t *ptep;
	unsigned char *vec = walk->private;
	int nr = (end - addr) >> PAGE_SHIFT;

	ptl = pmd_trans_huge_lock(pmd, vma);
	if (ptl) {
		memset(vec, 1, nr);
		spin_unlock(ptl);
		goto out;
	}

	if (pmd_trans_unstable(pmd)) {
		__mincore_unmapped_range(addr, end, vma, vec);
		goto out;
	}

	ptep = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
	for (; addr != end; ptep++, addr += PAGE_SIZE) {
		pte_t pte = *ptep;

		if (pte_none(pte))
			__mincore_unmapped_range(addr, addr + PAGE_SIZE,
						 vma, vec);
		else if (pte_present(pte))
			*vec = 1;
		else { /* pte is a swap entry */
			swp_entry_t entry = pte_to_swp_entry(pte);

			if (non_swap_entry(entry)) {
				/*
				 * migration or hwpoison entries are always
				 * uptodate
				 */
				*vec = 1;
			} else {
#ifdef CONFIG_SWAP
				*vec = mincore_page(swap_address_space(entry),
						    swp_offset(entry));
#else
				WARN_ON(1);
				*vec = 1;
#endif
			}
		}
		vec++;
	}
	pte_unmap_unlock(ptep - 1, ptl);
out:
	walk->private += nr;
	cond_resched();
	return 0;
}