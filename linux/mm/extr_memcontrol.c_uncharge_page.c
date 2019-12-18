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
struct uncharge_gather {unsigned int nr_huge; unsigned int nr_anon; unsigned int nr_file; unsigned int nr_shmem; struct page* dummy_page; int /*<<< orphan*/  nr_kmem; int /*<<< orphan*/  pgpgout; int /*<<< orphan*/ * memcg; } ;
struct page {int /*<<< orphan*/ * mem_cgroup; } ;

/* Variables and functions */
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHWPoison (struct page*) ; 
 int /*<<< orphan*/  PageKmemcg (struct page*) ; 
 int PageLRU (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __ClearPageKmemcg (struct page*) ; 
 unsigned int compound_nr (struct page*) ; 
 int /*<<< orphan*/  is_zone_device_page (struct page*) ; 
 scalar_t__ page_count (struct page*) ; 
 int /*<<< orphan*/  uncharge_batch (struct uncharge_gather*) ; 
 int /*<<< orphan*/  uncharge_gather_clear (struct uncharge_gather*) ; 

__attribute__((used)) static void uncharge_page(struct page *page, struct uncharge_gather *ug)
{
	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON_PAGE(page_count(page) && !is_zone_device_page(page) &&
			!PageHWPoison(page) , page);

	if (!page->mem_cgroup)
		return;

	/*
	 * Nobody should be changing or seriously looking at
	 * page->mem_cgroup at this point, we have fully
	 * exclusive access to the page.
	 */

	if (ug->memcg != page->mem_cgroup) {
		if (ug->memcg) {
			uncharge_batch(ug);
			uncharge_gather_clear(ug);
		}
		ug->memcg = page->mem_cgroup;
	}

	if (!PageKmemcg(page)) {
		unsigned int nr_pages = 1;

		if (PageTransHuge(page)) {
			nr_pages = compound_nr(page);
			ug->nr_huge += nr_pages;
		}
		if (PageAnon(page))
			ug->nr_anon += nr_pages;
		else {
			ug->nr_file += nr_pages;
			if (PageSwapBacked(page))
				ug->nr_shmem += nr_pages;
		}
		ug->pgpgout++;
	} else {
		ug->nr_kmem += compound_nr(page);
		__ClearPageKmemcg(page);
	}

	ug->dummy_page = page;
	page->mem_cgroup = NULL;
}