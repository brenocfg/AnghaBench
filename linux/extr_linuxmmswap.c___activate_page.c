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
struct lruvec {int dummy; } ;

/* Variables and functions */
 scalar_t__ LRU_ACTIVE ; 
 int /*<<< orphan*/  PGACTIVATE ; 
 int /*<<< orphan*/  PageActive (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  SetPageActive (struct page*) ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct page*,struct lruvec*,int) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int) ; 
 int page_is_file_cache (struct page*) ; 
 int page_lru_base_type (struct page*) ; 
 int /*<<< orphan*/  trace_mm_lru_activate (struct page*) ; 
 int /*<<< orphan*/  update_page_reclaim_stat (struct lruvec*,int,int) ; 

__attribute__((used)) static void __activate_page(struct page *page, struct lruvec *lruvec,
			    void *arg)
{
	if (PageLRU(page) && !PageActive(page) && !PageUnevictable(page)) {
		int file = page_is_file_cache(page);
		int lru = page_lru_base_type(page);

		del_page_from_lru_list(page, lruvec, lru);
		SetPageActive(page);
		lru += LRU_ACTIVE;
		add_page_to_lru_list(page, lruvec, lru);
		trace_mm_lru_activate(page);

		__count_vm_event(PGACTIVATE);
		update_page_reclaim_stat(lruvec, file, 1);
	}
}