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
struct swap_map_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_WRITE ; 
 int /*<<< orphan*/  flush_swap_writer (struct swap_map_handle*) ; 
 int /*<<< orphan*/  free_all_swap_pages (int /*<<< orphan*/ ) ; 
 int mark_swapfiles (struct swap_map_handle*,unsigned int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  release_swap_writer (struct swap_map_handle*) ; 
 int /*<<< orphan*/  root_swap ; 
 int /*<<< orphan*/  swsusp_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int swap_writer_finish(struct swap_map_handle *handle,
		unsigned int flags, int error)
{
	if (!error) {
		flush_swap_writer(handle);
		pr_info("S");
		error = mark_swapfiles(handle, flags);
		pr_cont("|\n");
	}

	if (error)
		free_all_swap_pages(root_swap);
	release_swap_writer(handle);
	swsusp_close(FMODE_WRITE);

	return error;
}