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
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int /*<<< orphan*/  ClearPageReferenced (struct page*) ; 
 scalar_t__ LRU_ACTIVE ; 
 int /*<<< orphan*/  PGDEACTIVATE ; 
 scalar_t__ PageActive (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct page*,struct lruvec*,int) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,scalar_t__) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 int page_is_file_cache (struct page*) ; 
 int page_lru_base_type (struct page*) ; 
 int /*<<< orphan*/  update_page_reclaim_stat (struct lruvec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lru_deactivate_fn(struct page *page, struct lruvec *lruvec,
			    void *arg)
{
	if (PageLRU(page) && PageActive(page) && !PageUnevictable(page)) {
		int file = page_is_file_cache(page);
		int lru = page_lru_base_type(page);

		del_page_from_lru_list(page, lruvec, lru + LRU_ACTIVE);
		ClearPageActive(page);
		ClearPageReferenced(page);
		add_page_to_lru_list(page, lruvec, lru);

		__count_vm_events(PGDEACTIVATE, hpage_nr_pages(page));
		update_page_reclaim_stat(lruvec, file, 0);
	}
}