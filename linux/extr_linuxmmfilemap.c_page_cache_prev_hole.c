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
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 
 scalar_t__ radix_tree_exceptional_entry (struct page*) ; 
 struct page* radix_tree_lookup (int /*<<< orphan*/ *,scalar_t__) ; 

pgoff_t page_cache_prev_hole(struct address_space *mapping,
			     pgoff_t index, unsigned long max_scan)
{
	unsigned long i;

	for (i = 0; i < max_scan; i++) {
		struct page *page;

		page = radix_tree_lookup(&mapping->i_pages, index);
		if (!page || radix_tree_exceptional_entry(page))
			break;
		index--;
		if (index == ULONG_MAX)
			break;
	}

	return index;
}