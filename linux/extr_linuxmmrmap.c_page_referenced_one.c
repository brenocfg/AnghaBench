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
struct page_vma_mapped_walk {unsigned long address; int /*<<< orphan*/  pmd; scalar_t__ pte; struct vm_area_struct* vma; struct page* page; } ;
struct page_referenced_arg {int vm_flags; int /*<<< orphan*/  mapcount; int /*<<< orphan*/  referenced; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TRANSPARENT_HUGEPAGE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int VM_LOCKED ; 
 int VM_SEQ_READ ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_page_idle (struct page*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ page_vma_mapped_walk (struct page_vma_mapped_walk*) ; 
 int /*<<< orphan*/  page_vma_mapped_walk_done (struct page_vma_mapped_walk*) ; 
 scalar_t__ pmdp_clear_flush_young_notify (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ ptep_clear_flush_young_notify (struct vm_area_struct*,unsigned long,scalar_t__) ; 
 scalar_t__ test_and_clear_page_young (struct page*) ; 

__attribute__((used)) static bool page_referenced_one(struct page *page, struct vm_area_struct *vma,
			unsigned long address, void *arg)
{
	struct page_referenced_arg *pra = arg;
	struct page_vma_mapped_walk pvmw = {
		.page = page,
		.vma = vma,
		.address = address,
	};
	int referenced = 0;

	while (page_vma_mapped_walk(&pvmw)) {
		address = pvmw.address;

		if (vma->vm_flags & VM_LOCKED) {
			page_vma_mapped_walk_done(&pvmw);
			pra->vm_flags |= VM_LOCKED;
			return false; /* To break the loop */
		}

		if (pvmw.pte) {
			if (ptep_clear_flush_young_notify(vma, address,
						pvmw.pte)) {
				/*
				 * Don't treat a reference through
				 * a sequentially read mapping as such.
				 * If the page has been used in another mapping,
				 * we will catch it; if this other mapping is
				 * already gone, the unmap path will have set
				 * PG_referenced or activated the page.
				 */
				if (likely(!(vma->vm_flags & VM_SEQ_READ)))
					referenced++;
			}
		} else if (IS_ENABLED(CONFIG_TRANSPARENT_HUGEPAGE)) {
			if (pmdp_clear_flush_young_notify(vma, address,
						pvmw.pmd))
				referenced++;
		} else {
			/* unexpected pmd-mapped page? */
			WARN_ON_ONCE(1);
		}

		pra->mapcount--;
	}

	if (referenced)
		clear_page_idle(page);
	if (test_and_clear_page_young(page))
		referenced++;

	if (referenced) {
		pra->referenced++;
		pra->vm_flags |= vma->vm_flags;
	}

	if (!pra->mapcount)
		return false; /* To break the loop */

	return true;
}