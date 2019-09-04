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
struct swsusp_info {int dummy; } ;
struct swap_map_handle {int dummy; } ;
struct snapshot_handle {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOSPC ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int SF_NOCOMPRESS_MODE ; 
 scalar_t__ data_of (struct snapshot_handle) ; 
 int /*<<< orphan*/  enough_swap (unsigned long) ; 
 int get_swap_writer (struct swap_map_handle*) ; 
 int /*<<< orphan*/  memset (struct snapshot_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int save_image (struct swap_map_handle*,struct snapshot_handle*,unsigned long) ; 
 int save_image_lzo (struct swap_map_handle*,struct snapshot_handle*,unsigned long) ; 
 unsigned long snapshot_get_image_size () ; 
 int snapshot_read_next (struct snapshot_handle*) ; 
 int swap_write_page (struct swap_map_handle*,struct swsusp_info*,int /*<<< orphan*/ *) ; 
 int swap_writer_finish (struct swap_map_handle*,unsigned int,int) ; 

int swsusp_write(unsigned int flags)
{
	struct swap_map_handle handle;
	struct snapshot_handle snapshot;
	struct swsusp_info *header;
	unsigned long pages;
	int error;

	pages = snapshot_get_image_size();
	error = get_swap_writer(&handle);
	if (error) {
		pr_err("Cannot get swap writer\n");
		return error;
	}
	if (flags & SF_NOCOMPRESS_MODE) {
		if (!enough_swap(pages)) {
			pr_err("Not enough free swap\n");
			error = -ENOSPC;
			goto out_finish;
		}
	}
	memset(&snapshot, 0, sizeof(struct snapshot_handle));
	error = snapshot_read_next(&snapshot);
	if (error < (int)PAGE_SIZE) {
		if (error >= 0)
			error = -EFAULT;

		goto out_finish;
	}
	header = (struct swsusp_info *)data_of(snapshot);
	error = swap_write_page(&handle, header, NULL);
	if (!error) {
		error = (flags & SF_NOCOMPRESS_MODE) ?
			save_image(&handle, &snapshot, pages - 1) :
			save_image_lzo(&handle, &snapshot, pages - 1);
	}
out_finish:
	error = swap_writer_finish(&handle, flags, error);
	return error;
}