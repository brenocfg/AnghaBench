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
struct vm_area_struct {int vm_flags; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PageMlocked (struct page*) ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  mlock_vma_page (struct page*) ; 
 int /*<<< orphan*/  munlock_vma_page (struct page*) ; 
 scalar_t__ pages_identical (struct page*,struct page*) ; 
 int replace_page (struct vm_area_struct*,struct page*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_stable_node (struct page*,int /*<<< orphan*/ *) ; 
 scalar_t__ split_huge_page (struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 scalar_t__ write_protect_page (struct vm_area_struct*,struct page*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int try_to_merge_one_page(struct vm_area_struct *vma,
				 struct page *page, struct page *kpage)
{
	pte_t orig_pte = __pte(0);
	int err = -EFAULT;

	if (page == kpage)			/* ksm page forked */
		return 0;

	if (!PageAnon(page))
		goto out;

	/*
	 * We need the page lock to read a stable PageSwapCache in
	 * write_protect_page().  We use trylock_page() instead of
	 * lock_page() because we don't want to wait here - we
	 * prefer to continue scanning and merging different pages,
	 * then come back to this page when it is unlocked.
	 */
	if (!trylock_page(page))
		goto out;

	if (PageTransCompound(page)) {
		if (split_huge_page(page))
			goto out_unlock;
	}

	/*
	 * If this anonymous page is mapped only here, its pte may need
	 * to be write-protected.  If it's mapped elsewhere, all of its
	 * ptes are necessarily already write-protected.  But in either
	 * case, we need to lock and check page_count is not raised.
	 */
	if (write_protect_page(vma, page, &orig_pte) == 0) {
		if (!kpage) {
			/*
			 * While we hold page lock, upgrade page from
			 * PageAnon+anon_vma to PageKsm+NULL stable_node:
			 * stable_tree_insert() will update stable_node.
			 */
			set_page_stable_node(page, NULL);
			mark_page_accessed(page);
			/*
			 * Page reclaim just frees a clean page with no dirty
			 * ptes: make sure that the ksm page would be swapped.
			 */
			if (!PageDirty(page))
				SetPageDirty(page);
			err = 0;
		} else if (pages_identical(page, kpage))
			err = replace_page(vma, page, kpage, orig_pte);
	}

	if ((vma->vm_flags & VM_LOCKED) && kpage && !err) {
		munlock_vma_page(page);
		if (!PageMlocked(kpage)) {
			unlock_page(page);
			lock_page(kpage);
			mlock_vma_page(kpage);
			page = kpage;		/* for final unlock */
		}
	}

out_unlock:
	unlock_page(page);
out:
	return err;
}