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
struct ubifs_pnode {size_t iip; TYPE_2__* parent; int /*<<< orphan*/  flags; int /*<<< orphan*/ * cnext; } ;
struct ubifs_info {int dirty_pn_cnt; } ;
struct TYPE_4__ {TYPE_1__* nbranch; } ;
struct TYPE_3__ {struct ubifs_pnode* pnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COW_CNODE ; 
 int /*<<< orphan*/  DIRTY_CNODE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ubifs_pnode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  OBSOLETE_CNODE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_pnode_dirt (struct ubifs_info*,struct ubifs_pnode*) ; 
 struct ubifs_pnode* kmemdup (struct ubifs_pnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_cats (struct ubifs_info*,struct ubifs_pnode*,struct ubifs_pnode*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ubifs_pnode *dirty_cow_pnode(struct ubifs_info *c,
					   struct ubifs_pnode *pnode)
{
	struct ubifs_pnode *p;

	if (!test_bit(COW_CNODE, &pnode->flags)) {
		/* pnode is not being committed */
		if (!test_and_set_bit(DIRTY_CNODE, &pnode->flags)) {
			c->dirty_pn_cnt += 1;
			add_pnode_dirt(c, pnode);
		}
		return pnode;
	}

	/* pnode is being committed, so copy it */
	p = kmemdup(pnode, sizeof(struct ubifs_pnode), GFP_NOFS);
	if (unlikely(!p))
		return ERR_PTR(-ENOMEM);

	p->cnext = NULL;
	__set_bit(DIRTY_CNODE, &p->flags);
	__clear_bit(COW_CNODE, &p->flags);
	replace_cats(c, pnode, p);

	ubifs_assert(c, !test_bit(OBSOLETE_CNODE, &pnode->flags));
	__set_bit(OBSOLETE_CNODE, &pnode->flags);

	c->dirty_pn_cnt += 1;
	add_pnode_dirt(c, pnode);
	pnode->parent->nbranch[p->iip].pnode = p;
	return p;
}