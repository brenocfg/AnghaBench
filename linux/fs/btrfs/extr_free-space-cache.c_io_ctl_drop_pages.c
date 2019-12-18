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
struct btrfs_io_ctl {int num_pages; scalar_t__* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (scalar_t__) ; 
 int /*<<< orphan*/  io_ctl_unmap_page (struct btrfs_io_ctl*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 
 int /*<<< orphan*/  unlock_page (scalar_t__) ; 

__attribute__((used)) static void io_ctl_drop_pages(struct btrfs_io_ctl *io_ctl)
{
	int i;

	io_ctl_unmap_page(io_ctl);

	for (i = 0; i < io_ctl->num_pages; i++) {
		if (io_ctl->pages[i]) {
			ClearPageChecked(io_ctl->pages[i]);
			unlock_page(io_ctl->pages[i]);
			put_page(io_ctl->pages[i]);
		}
	}
}