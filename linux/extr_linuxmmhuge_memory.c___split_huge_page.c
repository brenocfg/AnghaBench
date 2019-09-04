#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zone {int /*<<< orphan*/  zone_pgdat; } ;
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct lruvec {int dummy; } ;
struct list_head {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_pages; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SHMEM ; 
 int /*<<< orphan*/  ClearPageCompound (struct page*) ; 
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int HPAGE_PMD_NR ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  __delete_from_page_cache (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __split_huge_page_tail (struct page*,int,struct lruvec*,struct list_head*) ; 
 struct page* compound_head (struct page*) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_split_huge_fixup (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_inc (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remap_page (struct page*) ; 
 int /*<<< orphan*/  shmem_uncharge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  xa_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zone_lru_lock (struct zone*) ; 

__attribute__((used)) static void __split_huge_page(struct page *page, struct list_head *list,
		pgoff_t end, unsigned long flags)
{
	struct page *head = compound_head(page);
	struct zone *zone = page_zone(head);
	struct lruvec *lruvec;
	int i;

	lruvec = mem_cgroup_page_lruvec(head, zone->zone_pgdat);

	/* complete memcg works before add pages to LRU */
	mem_cgroup_split_huge_fixup(head);

	for (i = HPAGE_PMD_NR - 1; i >= 1; i--) {
		__split_huge_page_tail(head, i, lruvec, list);
		/* Some pages can be beyond i_size: drop them from page cache */
		if (head[i].index >= end) {
			ClearPageDirty(head + i);
			__delete_from_page_cache(head + i, NULL);
			if (IS_ENABLED(CONFIG_SHMEM) && PageSwapBacked(head))
				shmem_uncharge(head->mapping->host, 1);
			put_page(head + i);
		}
	}

	ClearPageCompound(head);
	/* See comment in __split_huge_page_tail() */
	if (PageAnon(head)) {
		/* Additional pin to radix tree of swap cache */
		if (PageSwapCache(head))
			page_ref_add(head, 2);
		else
			page_ref_inc(head);
	} else {
		/* Additional pin to radix tree */
		page_ref_add(head, 2);
		xa_unlock(&head->mapping->i_pages);
	}

	spin_unlock_irqrestore(zone_lru_lock(page_zone(head)), flags);

	remap_page(head);

	for (i = 0; i < HPAGE_PMD_NR; i++) {
		struct page *subpage = head + i;
		if (subpage == page)
			continue;
		unlock_page(subpage);

		/*
		 * Subpages may be freed if there wasn't any mapping
		 * like if add_to_swap() is running on a lru page that
		 * had its mapping zapped. And freeing these pages
		 * requires taking the lru_lock so we do the put_page
		 * of the tail pages after the split is complete.
		 */
		put_page(subpage);
	}
}