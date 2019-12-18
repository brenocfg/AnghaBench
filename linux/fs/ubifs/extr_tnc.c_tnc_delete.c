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
struct ubifs_znode {scalar_t__ level; int child_cnt; int iip; int /*<<< orphan*/  flags; scalar_t__ cnext; struct ubifs_znode* parent; struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {int /*<<< orphan*/  len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; TYPE_1__* znode; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {struct ubifs_znode* znode; int /*<<< orphan*/  len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {int fanout; int /*<<< orphan*/  clean_zn_cnt; int /*<<< orphan*/  dirty_zn_cnt; TYPE_2__ zroot; } ;
struct TYPE_3__ {int iip; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int /*<<< orphan*/  OBSOLETE_ZNODE ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_tnck (int /*<<< orphan*/ *,char*) ; 
 struct ubifs_znode* dirty_cow_znode (struct ubifs_info*,struct ubifs_zbranch*) ; 
 struct ubifs_znode* get_znode (struct ubifs_info*,struct ubifs_znode*,int /*<<< orphan*/ ) ; 
 int insert_old_idx (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int insert_old_idx_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_znode*) ; 
 int /*<<< orphan*/  lnc_free (struct ubifs_zbranch*) ; 
 int ubifs_add_dirt (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 
 int /*<<< orphan*/  ubifs_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int ubifs_zn_dirty (struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_zn_obsolete (struct ubifs_znode*) ; 

__attribute__((used)) static int tnc_delete(struct ubifs_info *c, struct ubifs_znode *znode, int n)
{
	struct ubifs_zbranch *zbr;
	struct ubifs_znode *zp;
	int i, err;

	/* Delete without merge for now */
	ubifs_assert(c, znode->level == 0);
	ubifs_assert(c, n >= 0 && n < c->fanout);
	dbg_tnck(&znode->zbranch[n].key, "deleting key ");

	zbr = &znode->zbranch[n];
	lnc_free(zbr);

	err = ubifs_add_dirt(c, zbr->lnum, zbr->len);
	if (err) {
		ubifs_dump_znode(c, znode);
		return err;
	}

	/* We do not "gap" zbranch slots */
	for (i = n; i < znode->child_cnt - 1; i++)
		znode->zbranch[i] = znode->zbranch[i + 1];
	znode->child_cnt -= 1;

	if (znode->child_cnt > 0)
		return 0;

	/*
	 * This was the last zbranch, we have to delete this znode from the
	 * parent.
	 */

	do {
		ubifs_assert(c, !ubifs_zn_obsolete(znode));
		ubifs_assert(c, ubifs_zn_dirty(znode));

		zp = znode->parent;
		n = znode->iip;

		atomic_long_dec(&c->dirty_zn_cnt);

		err = insert_old_idx_znode(c, znode);
		if (err)
			return err;

		if (znode->cnext) {
			__set_bit(OBSOLETE_ZNODE, &znode->flags);
			atomic_long_inc(&c->clean_zn_cnt);
			atomic_long_inc(&ubifs_clean_zn_cnt);
		} else
			kfree(znode);
		znode = zp;
	} while (znode->child_cnt == 1); /* while removing last child */

	/* Remove from znode, entry n - 1 */
	znode->child_cnt -= 1;
	ubifs_assert(c, znode->level != 0);
	for (i = n; i < znode->child_cnt; i++) {
		znode->zbranch[i] = znode->zbranch[i + 1];
		if (znode->zbranch[i].znode)
			znode->zbranch[i].znode->iip = i;
	}

	/*
	 * If this is the root and it has only 1 child then
	 * collapse the tree.
	 */
	if (!znode->parent) {
		while (znode->child_cnt == 1 && znode->level != 0) {
			zp = znode;
			zbr = &znode->zbranch[0];
			znode = get_znode(c, znode, 0);
			if (IS_ERR(znode))
				return PTR_ERR(znode);
			znode = dirty_cow_znode(c, zbr);
			if (IS_ERR(znode))
				return PTR_ERR(znode);
			znode->parent = NULL;
			znode->iip = 0;
			if (c->zroot.len) {
				err = insert_old_idx(c, c->zroot.lnum,
						     c->zroot.offs);
				if (err)
					return err;
			}
			c->zroot.lnum = zbr->lnum;
			c->zroot.offs = zbr->offs;
			c->zroot.len = zbr->len;
			c->zroot.znode = znode;
			ubifs_assert(c, !ubifs_zn_obsolete(zp));
			ubifs_assert(c, ubifs_zn_dirty(zp));
			atomic_long_dec(&c->dirty_zn_cnt);

			if (zp->cnext) {
				__set_bit(OBSOLETE_ZNODE, &zp->flags);
				atomic_long_inc(&c->clean_zn_cnt);
				atomic_long_inc(&ubifs_clean_zn_cnt);
			} else
				kfree(zp);
		}
	}

	return 0;
}