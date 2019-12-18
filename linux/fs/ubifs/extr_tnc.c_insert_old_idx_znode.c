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
struct ubifs_znode {size_t iip; TYPE_2__* parent; } ;
struct ubifs_zbranch {int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; scalar_t__ len; } ;
struct ubifs_info {TYPE_1__ zroot; } ;
struct TYPE_4__ {struct ubifs_zbranch* zbranch; } ;

/* Variables and functions */
 int insert_old_idx (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int insert_old_idx_znode(struct ubifs_info *c, struct ubifs_znode *znode)
{
	if (znode->parent) {
		struct ubifs_zbranch *zbr;

		zbr = &znode->parent->zbranch[znode->iip];
		if (zbr->len)
			return insert_old_idx(c, zbr->lnum, zbr->offs);
	} else
		if (c->zroot.len)
			return insert_old_idx(c, c->zroot.lnum,
					      c->zroot.offs);
	return 0;
}