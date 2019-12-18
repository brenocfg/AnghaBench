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
 int /*<<< orphan*/  compound_order (struct page*) ; 
 int /*<<< orphan*/  free_the_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page_testzero (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct page* virt_to_head_page (void*) ; 

void page_frag_free(void *addr)
{
	struct page *page = virt_to_head_page(addr);

	if (unlikely(put_page_testzero(page)))
		free_the_page(page, compound_order(page));
}