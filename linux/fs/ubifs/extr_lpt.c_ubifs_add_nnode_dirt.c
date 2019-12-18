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
struct ubifs_nnode {size_t iip; TYPE_1__* nbranch; struct ubifs_nnode* parent; } ;
struct ubifs_info {int lpt_drty_flgs; int /*<<< orphan*/  ltab_sz; int /*<<< orphan*/  ltab_lnum; int /*<<< orphan*/  nnode_sz; int /*<<< orphan*/  lpt_lnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  lnum; } ;

/* Variables and functions */
 int LTAB_DIRTY ; 
 int /*<<< orphan*/  ubifs_add_lpt_dirt (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ubifs_add_nnode_dirt(struct ubifs_info *c, struct ubifs_nnode *nnode)
{
	struct ubifs_nnode *np = nnode->parent;

	if (np)
		ubifs_add_lpt_dirt(c, np->nbranch[nnode->iip].lnum,
				   c->nnode_sz);
	else {
		ubifs_add_lpt_dirt(c, c->lpt_lnum, c->nnode_sz);
		if (!(c->lpt_drty_flgs & LTAB_DIRTY)) {
			c->lpt_drty_flgs |= LTAB_DIRTY;
			ubifs_add_lpt_dirt(c, c->ltab_lnum, c->ltab_sz);
		}
	}
}