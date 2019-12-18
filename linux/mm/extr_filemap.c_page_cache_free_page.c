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
struct page {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_2__ {void (* freepage ) (struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 scalar_t__ page_count (struct page*) ; 
 int /*<<< orphan*/  page_ref_sub (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void page_cache_free_page(struct address_space *mapping,
				struct page *page)
{
	void (*freepage)(struct page *);

	freepage = mapping->a_ops->freepage;
	if (freepage)
		freepage(page);

	if (PageTransHuge(page) && !PageHuge(page)) {
		page_ref_sub(page, HPAGE_PMD_NR);
		VM_BUG_ON_PAGE(page_count(page) <= 0, page);
	} else {
		put_page(page);
	}
}