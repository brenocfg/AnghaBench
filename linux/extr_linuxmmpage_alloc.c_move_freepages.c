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
struct zone {TYPE_1__* free_area; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/ * free_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageBuddy (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 scalar_t__ __PageMovable (struct page*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int page_order (struct page*) ; 
 scalar_t__ page_to_nid (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ page_zone (struct page*) ; 
 scalar_t__ pfn_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_valid_within (int /*<<< orphan*/ ) ; 
 scalar_t__ zone_to_nid (struct zone*) ; 

__attribute__((used)) static int move_freepages(struct zone *zone,
			  struct page *start_page, struct page *end_page,
			  int migratetype, int *num_movable)
{
	struct page *page;
	unsigned int order;
	int pages_moved = 0;

#ifndef CONFIG_HOLES_IN_ZONE
	/*
	 * page_zone is not safe to call in this context when
	 * CONFIG_HOLES_IN_ZONE is set. This bug check is probably redundant
	 * anyway as we check zone boundaries in move_freepages_block().
	 * Remove at a later date when no bug reports exist related to
	 * grouping pages by mobility
	 */
	VM_BUG_ON(pfn_valid(page_to_pfn(start_page)) &&
	          pfn_valid(page_to_pfn(end_page)) &&
	          page_zone(start_page) != page_zone(end_page));
#endif

	if (num_movable)
		*num_movable = 0;

	for (page = start_page; page <= end_page;) {
		if (!pfn_valid_within(page_to_pfn(page))) {
			page++;
			continue;
		}

		/* Make sure we are not inadvertently changing nodes */
		VM_BUG_ON_PAGE(page_to_nid(page) != zone_to_nid(zone), page);

		if (!PageBuddy(page)) {
			/*
			 * We assume that pages that could be isolated for
			 * migration are movable. But we don't actually try
			 * isolating, as that would be expensive.
			 */
			if (num_movable &&
					(PageLRU(page) || __PageMovable(page)))
				(*num_movable)++;

			page++;
			continue;
		}

		order = page_order(page);
		list_move(&page->lru,
			  &zone->free_area[order].free_list[migratetype]);
		page += 1 << order;
		pages_moved += 1 << order;
	}

	return pages_moved;
}