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
struct ubifs_info {scalar_t__ ohead_offs; int /*<<< orphan*/  ohead_lnum; int /*<<< orphan*/  orph_buf; int /*<<< orphan*/  min_io_size; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int ubifs_leb_change (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_prepare_node (struct ubifs_info*,int /*<<< orphan*/ ,int,int) ; 
 int ubifs_write_node (struct ubifs_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int do_write_orph_node(struct ubifs_info *c, int len, int atomic)
{
	int err = 0;

	if (atomic) {
		ubifs_assert(c, c->ohead_offs == 0);
		ubifs_prepare_node(c, c->orph_buf, len, 1);
		len = ALIGN(len, c->min_io_size);
		err = ubifs_leb_change(c, c->ohead_lnum, c->orph_buf, len);
	} else {
		if (c->ohead_offs == 0) {
			/* Ensure LEB has been unmapped */
			err = ubifs_leb_unmap(c, c->ohead_lnum);
			if (err)
				return err;
		}
		err = ubifs_write_node(c, c->orph_buf, len, c->ohead_lnum,
				       c->ohead_offs);
	}
	return err;
}