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
struct ubifs_nnode {size_t iip; int /*<<< orphan*/  flags; TYPE_1__* parent; } ;
struct ubifs_nbranch {int lnum; int offs; } ;
struct ubifs_info {int lpt_lnum; int lpt_offs; } ;
struct TYPE_2__ {struct ubifs_nbranch* nbranch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY_CNODE ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct ubifs_nnode* first_nnode (struct ubifs_info*,int*) ; 
 struct ubifs_nnode* next_nnode (struct ubifs_info*,struct ubifs_nnode*,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbg_is_nnode_dirty(struct ubifs_info *c, int lnum, int offs)
{
	struct ubifs_nnode *nnode;
	int hght;

	/* Entire tree is in memory so first_nnode / next_nnode are OK */
	nnode = first_nnode(c, &hght);
	for (; nnode; nnode = next_nnode(c, nnode, &hght)) {
		struct ubifs_nbranch *branch;

		cond_resched();
		if (nnode->parent) {
			branch = &nnode->parent->nbranch[nnode->iip];
			if (branch->lnum != lnum || branch->offs != offs)
				continue;
			if (test_bit(DIRTY_CNODE, &nnode->flags))
				return 1;
			return 0;
		} else {
			if (c->lpt_lnum != lnum || c->lpt_offs != offs)
				continue;
			if (test_bit(DIRTY_CNODE, &nnode->flags))
				return 1;
			return 0;
		}
	}
	return 1;
}