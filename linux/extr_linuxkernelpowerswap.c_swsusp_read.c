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
struct swsusp_info {scalar_t__ pages; } ;
struct swap_map_handle {int dummy; } ;
struct snapshot_handle {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int SF_NOCOMPRESS_MODE ; 
 scalar_t__ data_of (struct snapshot_handle) ; 
 int get_swap_reader (struct swap_map_handle*,unsigned int*) ; 
 int load_image (struct swap_map_handle*,struct snapshot_handle*,scalar_t__) ; 
 int load_image_lzo (struct swap_map_handle*,struct snapshot_handle*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct snapshot_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int snapshot_write_next (struct snapshot_handle*) ; 
 int swap_read_page (struct swap_map_handle*,struct swsusp_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_reader_finish (struct swap_map_handle*) ; 

int swsusp_read(unsigned int *flags_p)
{
	int error;
	struct swap_map_handle handle;
	struct snapshot_handle snapshot;
	struct swsusp_info *header;

	memset(&snapshot, 0, sizeof(struct snapshot_handle));
	error = snapshot_write_next(&snapshot);
	if (error < (int)PAGE_SIZE)
		return error < 0 ? error : -EFAULT;
	header = (struct swsusp_info *)data_of(snapshot);
	error = get_swap_reader(&handle, flags_p);
	if (error)
		goto end;
	if (!error)
		error = swap_read_page(&handle, header, NULL);
	if (!error) {
		error = (*flags_p & SF_NOCOMPRESS_MODE) ?
			load_image(&handle, &snapshot, header->pages - 1) :
			load_image_lzo(&handle, &snapshot, header->pages - 1);
	}
	swap_reader_finish(&handle);
end:
	if (!error)
		pr_debug("Image successfully loaded\n");
	else
		pr_debug("Error %d resuming\n", error);
	return error;
}