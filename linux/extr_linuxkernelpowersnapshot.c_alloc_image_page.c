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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swsusp_set_page_forbidden (struct page*) ; 
 int /*<<< orphan*/  swsusp_set_page_free (struct page*) ; 

__attribute__((used)) static struct page *alloc_image_page(gfp_t gfp_mask)
{
	struct page *page;

	page = alloc_page(gfp_mask);
	if (page) {
		swsusp_set_page_forbidden(page);
		swsusp_set_page_free(page);
	}
	return page;
}