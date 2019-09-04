#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_znode {size_t iip; TYPE_1__* parent; } ;
struct ubifs_zbranch {scalar_t__ len; scalar_t__ offs; scalar_t__ lnum; } ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ offs; scalar_t__ lnum; } ;
struct ubifs_info {TYPE_2__ zroot; } ;
struct TYPE_3__ {struct ubifs_zbranch* zbranch; } ;

/* Variables and functions */
 int insert_old_idx (struct ubifs_info*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ins_clr_old_idx_znode(struct ubifs_info *c,
				 struct ubifs_znode *znode)
{
	int err;

	if (znode->parent) {
		struct ubifs_zbranch *zbr;

		zbr = &znode->parent->zbranch[znode->iip];
		if (zbr->len) {
			err = insert_old_idx(c, zbr->lnum, zbr->offs);
			if (err)
				return err;
			zbr->lnum = 0;
			zbr->offs = 0;
			zbr->len = 0;
		}
	} else
		if (c->zroot.len) {
			err = insert_old_idx(c, c->zroot.lnum, c->zroot.offs);
			if (err)
				return err;
			c->zroot.lnum = 0;
			c->zroot.offs = 0;
			c->zroot.len = 0;
		}
	return 0;
}