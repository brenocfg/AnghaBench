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
struct extent_buffer {struct page** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_buffer_tree_ref (struct extent_buffer*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int num_extent_pages (struct extent_buffer*) ; 

__attribute__((used)) static void mark_extent_buffer_accessed(struct extent_buffer *eb,
		struct page *accessed)
{
	int num_pages, i;

	check_buffer_tree_ref(eb);

	num_pages = num_extent_pages(eb);
	for (i = 0; i < num_pages; i++) {
		struct page *p = eb->pages[i];

		if (p != accessed)
			mark_page_accessed(p);
	}
}