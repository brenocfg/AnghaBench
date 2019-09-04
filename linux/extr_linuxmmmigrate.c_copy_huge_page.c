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
struct hstate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_ORDER_NR_PAGES ; 
 scalar_t__ PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  __copy_gigantic_page (struct page*,struct page*,int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 int hpage_nr_pages (struct page*) ; 
 struct hstate* page_hstate (struct page*) ; 
 int pages_per_huge_page (struct hstate*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void copy_huge_page(struct page *dst, struct page *src)
{
	int i;
	int nr_pages;

	if (PageHuge(src)) {
		/* hugetlbfs page */
		struct hstate *h = page_hstate(src);
		nr_pages = pages_per_huge_page(h);

		if (unlikely(nr_pages > MAX_ORDER_NR_PAGES)) {
			__copy_gigantic_page(dst, src, nr_pages);
			return;
		}
	} else {
		/* thp page */
		BUG_ON(!PageTransHuge(src));
		nr_pages = hpage_nr_pages(src);
	}

	for (i = 0; i < nr_pages; i++) {
		cond_resched();
		copy_highpage(dst + i, src + i);
	}
}