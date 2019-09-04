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
struct ubifs_info {int /*<<< orphan*/  ubi; scalar_t__ ro_error; int /*<<< orphan*/  ro_mount; int /*<<< orphan*/  ro_media; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  dbg_is_tst_rcvry (struct ubifs_info*) ; 
 int dbg_leb_change (struct ubifs_info*,int,void const*,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int ubi_leb_change (int /*<<< orphan*/ ,int,void const*,int) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,int,int) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 

int ubifs_leb_change(struct ubifs_info *c, int lnum, const void *buf, int len)
{
	int err;

	ubifs_assert(c, !c->ro_media && !c->ro_mount);
	if (c->ro_error)
		return -EROFS;
	if (!dbg_is_tst_rcvry(c))
		err = ubi_leb_change(c->ubi, lnum, buf, len);
	else
		err = dbg_leb_change(c, lnum, buf, len);
	if (err) {
		ubifs_err(c, "changing %d bytes in LEB %d failed, error %d",
			  len, lnum, err);
		ubifs_ro_mode(c, err);
		dump_stack();
	}
	return err;
}