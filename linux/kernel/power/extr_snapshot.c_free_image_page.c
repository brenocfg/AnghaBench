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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  swsusp_unset_page_forbidden (struct page*) ; 
 int /*<<< orphan*/  swsusp_unset_page_free (struct page*) ; 
 int /*<<< orphan*/  virt_addr_valid (void*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static inline void free_image_page(void *addr, int clear_nosave_free)
{
	struct page *page;

	BUG_ON(!virt_addr_valid(addr));

	page = virt_to_page(addr);

	swsusp_unset_page_forbidden(page);
	if (clear_nosave_free)
		swsusp_unset_page_free(page);

	__free_page(page);
}