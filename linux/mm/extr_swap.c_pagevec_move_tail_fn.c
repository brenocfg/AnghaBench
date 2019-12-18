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
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  add_page_to_lru_list_tail (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_lru (struct page*) ; 

__attribute__((used)) static void pagevec_move_tail_fn(struct page *page, struct lruvec *lruvec,
				 void *arg)
{
	int *pgmoved = arg;

	if (PageLRU(page) && !PageUnevictable(page)) {
		del_page_from_lru_list(page, lruvec, page_lru(page));
		ClearPageActive(page);
		add_page_to_lru_list_tail(page, lruvec, page_lru(page));
		(*pgmoved)++;
	}
}