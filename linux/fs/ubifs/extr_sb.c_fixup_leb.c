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
struct ubifs_info {int min_io_size; int leb_size; int /*<<< orphan*/  sbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_mnt (char*,int,...) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_leb_change (struct ubifs_info*,int,int /*<<< orphan*/ ,int) ; 
 int ubifs_leb_read (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 

__attribute__((used)) static int fixup_leb(struct ubifs_info *c, int lnum, int len)
{
	int err;

	ubifs_assert(c, len >= 0);
	ubifs_assert(c, len % c->min_io_size == 0);
	ubifs_assert(c, len < c->leb_size);

	if (len == 0) {
		dbg_mnt("unmap empty LEB %d", lnum);
		return ubifs_leb_unmap(c, lnum);
	}

	dbg_mnt("fixup LEB %d, data len %d", lnum, len);
	err = ubifs_leb_read(c, lnum, c->sbuf, 0, len, 1);
	if (err)
		return err;

	return ubifs_leb_change(c, lnum, c->sbuf, len);
}