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
struct ubifs_nnode {int iip; TYPE_1__* nbranch; struct ubifs_nnode* parent; } ;
struct ubifs_info {int lpt_hght; } ;
struct TYPE_2__ {struct ubifs_nnode* nnode; } ;

/* Variables and functions */
 int UBIFS_LPT_FANOUT ; 

__attribute__((used)) static struct ubifs_nnode *next_nnode(struct ubifs_info *c,
				      struct ubifs_nnode *nnode, int *hght)
{
	struct ubifs_nnode *parent;
	int iip, h, i, found;

	parent = nnode->parent;
	if (!parent)
		return NULL;
	if (nnode->iip == UBIFS_LPT_FANOUT - 1) {
		*hght -= 1;
		return parent;
	}
	for (iip = nnode->iip + 1; iip < UBIFS_LPT_FANOUT; iip++) {
		nnode = parent->nbranch[iip].nnode;
		if (nnode)
			break;
	}
	if (!nnode) {
		*hght -= 1;
		return parent;
	}
	for (h = *hght + 1; h < c->lpt_hght; h++) {
		found = 0;
		for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
			if (nnode->nbranch[i].nnode) {
				found = 1;
				nnode = nnode->nbranch[i].nnode;
				*hght = h;
				break;
			}
		}
		if (!found)
			break;
	}
	return nnode;
}