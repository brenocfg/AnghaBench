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
struct extent_buffer {scalar_t__ len; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  copy_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 

void copy_extent_buffer_full(struct extent_buffer *dst,
			     struct extent_buffer *src)
{
	int i;
	int num_pages;

	ASSERT(dst->len == src->len);

	num_pages = num_extent_pages(dst);
	for (i = 0; i < num_pages; i++)
		copy_page(page_address(dst->pages[i]),
				page_address(src->pages[i]));
}