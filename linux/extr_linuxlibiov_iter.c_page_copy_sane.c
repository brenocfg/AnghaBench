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
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct page* compound_head (struct page*) ; 
 size_t compound_order (struct page*) ; 
 scalar_t__ likely (int) ; 
 size_t page_address (struct page*) ; 

__attribute__((used)) static inline bool page_copy_sane(struct page *page, size_t offset, size_t n)
{
	struct page *head = compound_head(page);
	size_t v = n + offset + page_address(page) - page_address(head);

	if (likely(n <= v && v <= (PAGE_SIZE << compound_order(head))))
		return true;
	WARN_ON(1);
	return false;
}