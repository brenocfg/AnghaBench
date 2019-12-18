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
struct swap_map_page {int dummy; } ;
struct swap_map_handle {scalar_t__ cur_swap; scalar_t__ first_sector; int /*<<< orphan*/  reqd_free_pages; scalar_t__ k; struct swap_map_page* cur; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ alloc_swapdev_block (int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  release_swap_writer (struct swap_map_handle*) ; 
 int /*<<< orphan*/  reqd_free_pages () ; 
 int /*<<< orphan*/  root_swap ; 
 int /*<<< orphan*/  swsusp_close (int /*<<< orphan*/ ) ; 
 int swsusp_swap_check () ; 

__attribute__((used)) static int get_swap_writer(struct swap_map_handle *handle)
{
	int ret;

	ret = swsusp_swap_check();
	if (ret) {
		if (ret != -ENOSPC)
			pr_err("Cannot find swap device, try swapon -a\n");
		return ret;
	}
	handle->cur = (struct swap_map_page *)get_zeroed_page(GFP_KERNEL);
	if (!handle->cur) {
		ret = -ENOMEM;
		goto err_close;
	}
	handle->cur_swap = alloc_swapdev_block(root_swap);
	if (!handle->cur_swap) {
		ret = -ENOSPC;
		goto err_rel;
	}
	handle->k = 0;
	handle->reqd_free_pages = reqd_free_pages();
	handle->first_sector = handle->cur_swap;
	return 0;
err_rel:
	release_swap_writer(handle);
err_close:
	swsusp_close(FMODE_WRITE);
	return ret;
}