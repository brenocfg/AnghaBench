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
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int /*<<< orphan*/  drain_all_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_slab_node (int /*<<< orphan*/ ) ; 
 scalar_t__ is_free_buddy_page (struct page*) ; 
 int /*<<< orphan*/  lru_add_drain_all () ; 
 int /*<<< orphan*/  page_to_nid (struct page*) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 

void shake_page(struct page *p, int access)
{
	if (PageHuge(p))
		return;

	if (!PageSlab(p)) {
		lru_add_drain_all();
		if (PageLRU(p))
			return;
		drain_all_pages(page_zone(p));
		if (PageLRU(p) || is_free_buddy_page(p))
			return;
	}

	/*
	 * Only call shrink_node_slabs here (which would also shrink
	 * other caches) if access is not potentially fatal.
	 */
	if (access)
		drop_slab_node(page_to_nid(p));
}