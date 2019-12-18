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
struct ubifs_info {int min_io_size; int leb_cnt; int leb_size; scalar_t__ ro_error; int /*<<< orphan*/  space_fixup; int /*<<< orphan*/  ro_mount; int /*<<< orphan*/  ro_media; } ;
struct ubifs_ch {int /*<<< orphan*/  node_type; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EROFS ; 
 int /*<<< orphan*/  dbg_io (char*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dbg_ntype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_dump_node (struct ubifs_info*,void*) ; 
 int ubifs_leb_write (struct ubifs_info*,int,void*,int,int) ; 
 int ubifs_prepare_node_hmac (struct ubifs_info*,void*,int,int,int) ; 

int ubifs_write_node_hmac(struct ubifs_info *c, void *buf, int len, int lnum,
			  int offs, int hmac_offs)
{
	int err, buf_len = ALIGN(len, c->min_io_size);

	dbg_io("LEB %d:%d, %s, length %d (aligned %d)",
	       lnum, offs, dbg_ntype(((struct ubifs_ch *)buf)->node_type), len,
	       buf_len);
	ubifs_assert(c, lnum >= 0 && lnum < c->leb_cnt && offs >= 0);
	ubifs_assert(c, offs % c->min_io_size == 0 && offs < c->leb_size);
	ubifs_assert(c, !c->ro_media && !c->ro_mount);
	ubifs_assert(c, !c->space_fixup);

	if (c->ro_error)
		return -EROFS;

	err = ubifs_prepare_node_hmac(c, buf, len, hmac_offs, 1);
	if (err)
		return err;

	err = ubifs_leb_write(c, lnum, buf, offs, buf_len);
	if (err)
		ubifs_dump_node(c, buf);

	return err;
}