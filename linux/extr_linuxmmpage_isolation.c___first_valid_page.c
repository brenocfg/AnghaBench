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
 struct page* pfn_to_online_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid_within (unsigned long) ; 

__attribute__((used)) static inline struct page *
__first_valid_page(unsigned long pfn, unsigned long nr_pages)
{
	int i;

	for (i = 0; i < nr_pages; i++) {
		struct page *page;

		if (!pfn_valid_within(pfn + i))
			continue;
		page = pfn_to_online_page(pfn + i);
		if (!page)
			continue;
		return page;
	}
	return NULL;
}