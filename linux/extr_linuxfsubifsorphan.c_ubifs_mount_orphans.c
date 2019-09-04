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
struct ubifs_info {int /*<<< orphan*/  orph_buf; int /*<<< orphan*/  leb_size; int /*<<< orphan*/  max_orphans; } ;

/* Variables and functions */
 int ENOMEM ; 
 int kill_orphans (struct ubifs_info*) ; 
 int /*<<< orphan*/  tot_avail_orphs (struct ubifs_info*) ; 
 int ubifs_clear_orphans (struct ubifs_info*) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

int ubifs_mount_orphans(struct ubifs_info *c, int unclean, int read_only)
{
	int err = 0;

	c->max_orphans = tot_avail_orphs(c);

	if (!read_only) {
		c->orph_buf = vmalloc(c->leb_size);
		if (!c->orph_buf)
			return -ENOMEM;
	}

	if (unclean)
		err = kill_orphans(c);
	else if (!read_only)
		err = ubifs_clear_orphans(c);

	return err;
}