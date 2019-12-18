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
struct btrfs_io_ctl {int /*<<< orphan*/ * orig; int /*<<< orphan*/ * cur; } ;

/* Variables and functions */

__attribute__((used)) static void io_ctl_unmap_page(struct btrfs_io_ctl *io_ctl)
{
	if (io_ctl->cur) {
		io_ctl->cur = NULL;
		io_ctl->orig = NULL;
	}
}