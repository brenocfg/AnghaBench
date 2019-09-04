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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct page {scalar_t__ mapping; } ;
struct mm_struct {int dummy; } ;
struct dev_pagemap {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int EFAULT ; 
 struct page* ERR_PTR (int) ; 
 unsigned int FOLL_DUMP ; 
 unsigned int FOLL_GET ; 
 unsigned int FOLL_MIGRATION ; 
 unsigned int FOLL_MLOCK ; 
 unsigned int FOLL_NUMA ; 
 unsigned int FOLL_SPLIT ; 
 unsigned int FOLL_TOUCH ; 
 unsigned int FOLL_WRITE ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  can_follow_write_pte (int /*<<< orphan*/ ,unsigned int) ; 
 int follow_pfn_pte (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct dev_pagemap* get_dev_pagemap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  is_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  migration_entry_wait (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mlock_vma_page (struct page*) ; 
 struct page* no_page_table (struct vm_area_struct*,unsigned int) ; 
 int pmd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_protnone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dev_pagemap (struct dev_pagemap*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int split_huge_page (struct page*) ; 
 scalar_t__ trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *follow_page_pte(struct vm_area_struct *vma,
		unsigned long address, pmd_t *pmd, unsigned int flags)
{
	struct mm_struct *mm = vma->vm_mm;
	struct dev_pagemap *pgmap = NULL;
	struct page *page;
	spinlock_t *ptl;
	pte_t *ptep, pte;

retry:
	if (unlikely(pmd_bad(*pmd)))
		return no_page_table(vma, flags);

	ptep = pte_offset_map_lock(mm, pmd, address, &ptl);
	pte = *ptep;
	if (!pte_present(pte)) {
		swp_entry_t entry;
		/*
		 * KSM's break_ksm() relies upon recognizing a ksm page
		 * even while it is being migrated, so for that case we
		 * need migration_entry_wait().
		 */
		if (likely(!(flags & FOLL_MIGRATION)))
			goto no_page;
		if (pte_none(pte))
			goto no_page;
		entry = pte_to_swp_entry(pte);
		if (!is_migration_entry(entry))
			goto no_page;
		pte_unmap_unlock(ptep, ptl);
		migration_entry_wait(mm, pmd, address);
		goto retry;
	}
	if ((flags & FOLL_NUMA) && pte_protnone(pte))
		goto no_page;
	if ((flags & FOLL_WRITE) && !can_follow_write_pte(pte, flags)) {
		pte_unmap_unlock(ptep, ptl);
		return NULL;
	}

	page = vm_normal_page(vma, address, pte);
	if (!page && pte_devmap(pte) && (flags & FOLL_GET)) {
		/*
		 * Only return device mapping pages in the FOLL_GET case since
		 * they are only valid while holding the pgmap reference.
		 */
		pgmap = get_dev_pagemap(pte_pfn(pte), NULL);
		if (pgmap)
			page = pte_page(pte);
		else
			goto no_page;
	} else if (unlikely(!page)) {
		if (flags & FOLL_DUMP) {
			/* Avoid special (like zero) pages in core dumps */
			page = ERR_PTR(-EFAULT);
			goto out;
		}

		if (is_zero_pfn(pte_pfn(pte))) {
			page = pte_page(pte);
		} else {
			int ret;

			ret = follow_pfn_pte(vma, address, ptep, flags);
			page = ERR_PTR(ret);
			goto out;
		}
	}

	if (flags & FOLL_SPLIT && PageTransCompound(page)) {
		int ret;
		get_page(page);
		pte_unmap_unlock(ptep, ptl);
		lock_page(page);
		ret = split_huge_page(page);
		unlock_page(page);
		put_page(page);
		if (ret)
			return ERR_PTR(ret);
		goto retry;
	}

	if (flags & FOLL_GET) {
		get_page(page);

		/* drop the pgmap reference now that we hold the page */
		if (pgmap) {
			put_dev_pagemap(pgmap);
			pgmap = NULL;
		}
	}
	if (flags & FOLL_TOUCH) {
		if ((flags & FOLL_WRITE) &&
		    !pte_dirty(pte) && !PageDirty(page))
			set_page_dirty(page);
		/*
		 * pte_mkyoung() would be more correct here, but atomic care
		 * is needed to avoid losing the dirty bit: it is easier to use
		 * mark_page_accessed().
		 */
		mark_page_accessed(page);
	}
	if ((flags & FOLL_MLOCK) && (vma->vm_flags & VM_LOCKED)) {
		/* Do not mlock pte-mapped THP */
		if (PageTransCompound(page))
			goto out;

		/*
		 * The preliminary mapping check is mainly to avoid the
		 * pointless overhead of lock_page on the ZERO_PAGE
		 * which might bounce very badly if there is contention.
		 *
		 * If the page is already locked, we don't need to
		 * handle it now - vmscan will handle it later if and
		 * when it attempts to reclaim the page.
		 */
		if (page->mapping && trylock_page(page)) {
			lru_add_drain();  /* push cached pages to LRU */
			/*
			 * Because we lock page here, and migration is
			 * blocked by the pte's page reference, and we
			 * know the page is still mapped, we don't even
			 * need to check for file-cache page truncation.
			 */
			mlock_vma_page(page);
			unlock_page(page);
		}
	}
out:
	pte_unmap_unlock(ptep, ptl);
	return page;
no_page:
	pte_unmap_unlock(ptep, ptl);
	if (!pte_none(pte))
		return NULL;
	return no_page_table(vma, flags);
}