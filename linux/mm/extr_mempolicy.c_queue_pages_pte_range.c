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
struct queue_pages {unsigned long flags; int /*<<< orphan*/  pagelist; } ;
struct page {int dummy; } ;
struct mm_walk {int /*<<< orphan*/  mm; struct queue_pages* private; struct vm_area_struct* vma; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int EIO ; 
 unsigned long MPOL_MF_MOVE ; 
 unsigned long MPOL_MF_MOVE_ALL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PageReserved (struct page*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ migrate_page_add (struct page*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * pmd_trans_huge_lock (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 scalar_t__ pmd_trans_unstable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int queue_pages_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,unsigned long,struct mm_walk*) ; 
 int /*<<< orphan*/  queue_pages_required (struct page*,struct queue_pages*) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_migratable (struct vm_area_struct*) ; 

__attribute__((used)) static int queue_pages_pte_range(pmd_t *pmd, unsigned long addr,
			unsigned long end, struct mm_walk *walk)
{
	struct vm_area_struct *vma = walk->vma;
	struct page *page;
	struct queue_pages *qp = walk->private;
	unsigned long flags = qp->flags;
	int ret;
	bool has_unmovable = false;
	pte_t *pte;
	spinlock_t *ptl;

	ptl = pmd_trans_huge_lock(pmd, vma);
	if (ptl) {
		ret = queue_pages_pmd(pmd, ptl, addr, end, walk);
		if (ret != 2)
			return ret;
	}
	/* THP was split, fall through to pte walk */

	if (pmd_trans_unstable(pmd))
		return 0;

	pte = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
	for (; addr != end; pte++, addr += PAGE_SIZE) {
		if (!pte_present(*pte))
			continue;
		page = vm_normal_page(vma, addr, *pte);
		if (!page)
			continue;
		/*
		 * vm_normal_page() filters out zero pages, but there might
		 * still be PageReserved pages to skip, perhaps in a VDSO.
		 */
		if (PageReserved(page))
			continue;
		if (!queue_pages_required(page, qp))
			continue;
		if (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) {
			/* MPOL_MF_STRICT must be specified if we get here */
			if (!vma_migratable(vma)) {
				has_unmovable = true;
				break;
			}

			/*
			 * Do not abort immediately since there may be
			 * temporary off LRU pages in the range.  Still
			 * need migrate other LRU pages.
			 */
			if (migrate_page_add(page, qp->pagelist, flags))
				has_unmovable = true;
		} else
			break;
	}
	pte_unmap_unlock(pte - 1, ptl);
	cond_resched();

	if (has_unmovable)
		return 1;

	return addr != end ? -EIO : 0;
}