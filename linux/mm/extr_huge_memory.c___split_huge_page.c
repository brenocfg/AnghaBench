#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ swp_entry_t ;
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct lruvec {int dummy; } ;
struct list_head {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ pgoff_t ;
struct TYPE_10__ {int /*<<< orphan*/  lru_lock; } ;
typedef  TYPE_3__ pg_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_pages; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SHMEM ; 
 int /*<<< orphan*/  ClearPageCompound (struct page*) ; 
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  HPAGE_PMD_ORDER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  __delete_from_page_cache (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __split_huge_page_tail (struct page*,int,struct lruvec*,struct list_head*) ; 
 int /*<<< orphan*/  __xa_store (int /*<<< orphan*/ *,unsigned long,struct page*,int /*<<< orphan*/ ) ; 
 struct page* compound_head (struct page*) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,TYPE_3__*) ; 
 int /*<<< orphan*/  mem_cgroup_split_huge_fixup (struct page*) ; 
 TYPE_3__* page_pgdat (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_inc (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  remap_page (struct page*) ; 
 int /*<<< orphan*/  shmem_uncharge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  split_page_owner (struct page*,int /*<<< orphan*/ ) ; 
 struct address_space* swap_address_space (TYPE_2__) ; 
 unsigned long swp_offset (TYPE_2__) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  xa_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __split_huge_page(struct page *page, struct list_head *list,
		pgoff_t end, unsigned long flags)
{
	struct page *head = compound_head(page);
	pg_data_t *pgdat = page_pgdat(head);
	struct lruvec *lruvec;
	struct address_space *swap_cache = NULL;
	unsigned long offset = 0;
	int i;

	lruvec = mem_cgroup_page_lruvec(head, pgdat);

	/* complete memcg works before add pages to LRU */
	mem_cgroup_split_huge_fixup(head);

	if (PageAnon(head) && PageSwapCache(head)) {
		swp_entry_t entry = { .val = page_private(head) };

		offset = swp_offset(entry);
		swap_cache = swap_address_space(entry);
		xa_lock(&swap_cache->i_pages);
	}

	for (i = HPAGE_PMD_NR - 1; i >= 1; i--) {
		__split_huge_page_tail(head, i, lruvec, list);
		/* Some pages can be beyond i_size: drop them from page cache */
		if (head[i].index >= end) {
			ClearPageDirty(head + i);
			__delete_from_page_cache(head + i, NULL);
			if (IS_ENABLED(CONFIG_SHMEM) && PageSwapBacked(head))
				shmem_uncharge(head->mapping->host, 1);
			put_page(head + i);
		} else if (!PageAnon(page)) {
			__xa_store(&head->mapping->i_pages, head[i].index,
					head + i, 0);
		} else if (swap_cache) {
			__xa_store(&swap_cache->i_pages, offset + i,
					head + i, 0);
		}
	}

	ClearPageCompound(head);

	split_page_owner(head, HPAGE_PMD_ORDER);

	/* See comment in __split_huge_page_tail() */
	if (PageAnon(head)) {
		/* Additional pin to swap cache */
		if (PageSwapCache(head)) {
			page_ref_add(head, 2);
			xa_unlock(&swap_cache->i_pages);
		} else {
			page_ref_inc(head);
		}
	} else {
		/* Additional pin to page cache */
		page_ref_add(head, 2);
		xa_unlock(&head->mapping->i_pages);
	}

	spin_unlock_irqrestore(&pgdat->lru_lock, flags);

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