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
struct ubifs_nnode {size_t iip; struct ubifs_nnode* parent; int /*<<< orphan*/  flags; struct ubifs_nbranch* nbranch; } ;
struct ubifs_nbranch {int lnum; int offs; } ;
struct ubifs_info {int lpt_lnum; int lpt_offs; int dirty_nn_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY_CNODE ; 
 scalar_t__ IS_ERR (struct ubifs_nnode*) ; 
 int PTR_ERR (struct ubifs_nnode*) ; 
 struct ubifs_nnode* nnode_lookup (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_add_nnode_dirt (struct ubifs_info*,struct ubifs_nnode*) ; 

__attribute__((used)) static int make_nnode_dirty(struct ubifs_info *c, int node_num, int lnum,
			    int offs)
{
	struct ubifs_nnode *nnode;

	nnode = nnode_lookup(c, node_num);
	if (IS_ERR(nnode))
		return PTR_ERR(nnode);
	if (nnode->parent) {
		struct ubifs_nbranch *branch;

		branch = &nnode->parent->nbranch[nnode->iip];
		if (branch->lnum != lnum || branch->offs != offs)
			return 0; /* nnode is obsolete */
	} else if (c->lpt_lnum != lnum || c->lpt_offs != offs)
			return 0; /* nnode is obsolete */
	/* Assumes cnext list is empty i.e. not called during commit */
	if (!test_and_set_bit(DIRTY_CNODE, &nnode->flags)) {
		c->dirty_nn_cnt += 1;
		ubifs_add_nnode_dirt(c, nnode);
		/* Mark parent and ancestors dirty too */
		nnode = nnode->parent;
		while (nnode) {
			if (!test_and_set_bit(DIRTY_CNODE, &nnode->flags)) {
				c->dirty_nn_cnt += 1;
				ubifs_add_nnode_dirt(c, nnode);
				nnode = nnode->parent;
			} else
				break;
		}
	}
	return 0;
}