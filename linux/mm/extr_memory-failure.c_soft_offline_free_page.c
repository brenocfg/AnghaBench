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
 int EBUSY ; 
 int dissolve_free_huge_page (struct page*) ; 
 int /*<<< orphan*/  num_poisoned_pages_inc () ; 
 scalar_t__ set_hwpoison_free_buddy_page (struct page*) ; 

__attribute__((used)) static int soft_offline_free_page(struct page *page)
{
	int rc = dissolve_free_huge_page(page);

	if (!rc) {
		if (set_hwpoison_free_buddy_page(page))
			num_poisoned_pages_inc();
		else
			rc = -EBUSY;
	}
	return rc;
}