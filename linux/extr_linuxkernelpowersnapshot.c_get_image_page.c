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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_unsafe_pages ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 scalar_t__ swsusp_page_is_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swsusp_set_page_forbidden (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swsusp_set_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static void *get_image_page(gfp_t gfp_mask, int safe_needed)
{
	void *res;

	res = (void *)get_zeroed_page(gfp_mask);
	if (safe_needed)
		while (res && swsusp_page_is_free(virt_to_page(res))) {
			/* The page is unsafe, mark it for swsusp_free() */
			swsusp_set_page_forbidden(virt_to_page(res));
			allocated_unsafe_pages++;
			res = (void *)get_zeroed_page(gfp_mask);
		}
	if (res) {
		swsusp_set_page_forbidden(virt_to_page(res));
		swsusp_set_page_free(virt_to_page(res));
	}
	return res;
}