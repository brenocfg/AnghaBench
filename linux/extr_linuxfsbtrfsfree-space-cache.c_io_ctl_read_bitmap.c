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
struct btrfs_io_ctl {int /*<<< orphan*/  cur; int /*<<< orphan*/  index; } ;
struct btrfs_free_space {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int io_ctl_check_crc (struct btrfs_io_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_ctl_unmap_page (struct btrfs_io_ctl*) ; 

__attribute__((used)) static int io_ctl_read_bitmap(struct btrfs_io_ctl *io_ctl,
			      struct btrfs_free_space *entry)
{
	int ret;

	ret = io_ctl_check_crc(io_ctl, io_ctl->index);
	if (ret)
		return ret;

	copy_page(entry->bitmap, io_ctl->cur);
	io_ctl_unmap_page(io_ctl);

	return 0;
}