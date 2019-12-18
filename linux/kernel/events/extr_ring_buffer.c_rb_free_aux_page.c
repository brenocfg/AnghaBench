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
struct ring_buffer {int /*<<< orphan*/ * aux_pages; } ;
struct page {int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb_free_aux_page(struct ring_buffer *rb, int idx)
{
	struct page *page = virt_to_page(rb->aux_pages[idx]);

	ClearPagePrivate(page);
	page->mapping = NULL;
	__free_page(page);
}