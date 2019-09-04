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
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 scalar_t__ get_page_unless_zero (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

int get_hwpoison_page(struct page *page)
{
	struct page *head = compound_head(page);

	if (!PageHuge(head) && PageTransHuge(head)) {
		/*
		 * Non anonymous thp exists only in allocation/free time. We
		 * can't handle such a case correctly, so let's give it up.
		 * This should be better than triggering BUG_ON when kernel
		 * tries to touch the "partially handled" page.
		 */
		if (!PageAnon(head)) {
			pr_err("Memory failure: %#lx: non anonymous thp\n",
				page_to_pfn(page));
			return 0;
		}
	}

	if (get_page_unless_zero(head)) {
		if (head == compound_head(page))
			return 1;

		pr_info("Memory failure: %#lx cannot catch tail\n",
			page_to_pfn(page));
		put_page(head);
	}

	return 0;
}