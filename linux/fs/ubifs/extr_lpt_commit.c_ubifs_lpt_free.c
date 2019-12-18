#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ubifs_nnode {TYPE_1__* nbranch; } ;
struct TYPE_6__ {int /*<<< orphan*/ * arr; } ;
struct ubifs_info {int /*<<< orphan*/ * lpt_nod_buf; int /*<<< orphan*/ * ltab; int /*<<< orphan*/ * nroot; TYPE_3__ dirty_idx; TYPE_2__* lpt_heap; int /*<<< orphan*/ * lsave; int /*<<< orphan*/ * lpt_buf; int /*<<< orphan*/ * ltab_cmt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * arr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nnode; } ;

/* Variables and functions */
 int LPROPS_HEAP_CNT ; 
 int UBIFS_LPT_FANOUT ; 
 struct ubifs_nnode* first_nnode (struct ubifs_info*,int*) ; 
 int /*<<< orphan*/  free_obsolete_cnodes (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct ubifs_nnode* next_nnode (struct ubifs_info*,struct ubifs_nnode*,int*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

void ubifs_lpt_free(struct ubifs_info *c, int wr_only)
{
	struct ubifs_nnode *nnode;
	int i, hght;

	/* Free write-only things first */

	free_obsolete_cnodes(c); /* Leftover from a failed commit */

	vfree(c->ltab_cmt);
	c->ltab_cmt = NULL;
	vfree(c->lpt_buf);
	c->lpt_buf = NULL;
	kfree(c->lsave);
	c->lsave = NULL;

	if (wr_only)
		return;

	/* Now free the rest */

	nnode = first_nnode(c, &hght);
	while (nnode) {
		for (i = 0; i < UBIFS_LPT_FANOUT; i++)
			kfree(nnode->nbranch[i].nnode);
		nnode = next_nnode(c, nnode, &hght);
	}
	for (i = 0; i < LPROPS_HEAP_CNT; i++)
		kfree(c->lpt_heap[i].arr);
	kfree(c->dirty_idx.arr);
	kfree(c->nroot);
	vfree(c->ltab);
	kfree(c->lpt_nod_buf);
}