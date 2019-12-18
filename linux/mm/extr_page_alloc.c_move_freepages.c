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
struct zone {int /*<<< orphan*/ * free_area; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageBuddy (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 scalar_t__ __PageMovable (struct page*) ; 
 int /*<<< orphan*/  move_to_free_area (struct page*,int /*<<< orphan*/ *,int) ; 
 unsigned int page_order (struct page*) ; 
 scalar_t__ page_to_nid (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  pfn_valid_within (int /*<<< orphan*/ ) ; 
 scalar_t__ zone_to_nid (struct zone*) ; 

__attribute__((used)) static int move_freepages(struct zone *zone,
			  struct page *start_page, struct page *end_page,
			  int migratetype, int *num_movable)
{
	struct page *page;
	unsigned int order;
	int pages_moved = 0;

	for (page = start_page; page <= end_page;) {
		if (!pfn_valid_within(page_to_pfn(page))) {
			page++;
			continue;
		}

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

		/* Make sure we are not inadvertently changing nodes */
		VM_BUG_ON_PAGE(page_to_nid(page) != zone_to_nid(zone), page);
		VM_BUG_ON_PAGE(page_zone(page) != zone, page);

		order = page_order(page);
		move_to_free_area(page, &zone->free_area[order], migratetype);
		page += 1 << order;
		pages_moved += 1 << order;
	}

	return pages_moved;
}