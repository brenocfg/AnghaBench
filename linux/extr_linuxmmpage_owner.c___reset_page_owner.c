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
struct page_ext {int /*<<< orphan*/  flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_EXT_OWNER ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page_ext* lookup_page_ext (struct page*) ; 
 scalar_t__ unlikely (int) ; 

void __reset_page_owner(struct page *page, unsigned int order)
{
	int i;
	struct page_ext *page_ext;

	for (i = 0; i < (1 << order); i++) {
		page_ext = lookup_page_ext(page + i);
		if (unlikely(!page_ext))
			continue;
		__clear_bit(PAGE_EXT_OWNER, &page_ext->flags);
	}
}