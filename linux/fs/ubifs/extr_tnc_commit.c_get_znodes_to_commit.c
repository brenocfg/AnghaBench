#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubifs_znode {struct ubifs_znode* cnext; int /*<<< orphan*/  iip; int /*<<< orphan*/  ciip; int /*<<< orphan*/  parent; int /*<<< orphan*/  cparent; scalar_t__ alt; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  znode; } ;
struct ubifs_info {int /*<<< orphan*/  dirty_zn_cnt; struct ubifs_znode* cnext; struct ubifs_znode* enext; TYPE_1__ zroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_cmt (char*,...) ; 
 struct ubifs_znode* find_first_dirty (int /*<<< orphan*/ ) ; 
 struct ubifs_znode* find_next_dirty (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_zn_cow (struct ubifs_znode*) ; 

__attribute__((used)) static int get_znodes_to_commit(struct ubifs_info *c)
{
	struct ubifs_znode *znode, *cnext;
	int cnt = 0;

	c->cnext = find_first_dirty(c->zroot.znode);
	znode = c->enext = c->cnext;
	if (!znode) {
		dbg_cmt("no znodes to commit");
		return 0;
	}
	cnt += 1;
	while (1) {
		ubifs_assert(c, !ubifs_zn_cow(znode));
		__set_bit(COW_ZNODE, &znode->flags);
		znode->alt = 0;
		cnext = find_next_dirty(znode);
		if (!cnext) {
			znode->cnext = c->cnext;
			break;
		}
		znode->cparent = znode->parent;
		znode->ciip = znode->iip;
		znode->cnext = cnext;
		znode = cnext;
		cnt += 1;
	}
	dbg_cmt("committing %d znodes", cnt);
	ubifs_assert(c, cnt == atomic_long_read(&c->dirty_zn_cnt));
	return cnt;
}