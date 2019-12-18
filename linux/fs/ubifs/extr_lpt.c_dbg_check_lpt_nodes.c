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
struct ubifs_pnode {int dummy; } ;
struct ubifs_nnode {TYPE_1__* nbranch; int /*<<< orphan*/  num; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_cnode {int num; int iip; scalar_t__ level; struct ubifs_nnode* parent; } ;
struct TYPE_2__ {struct ubifs_cnode* cnode; } ;

/* Variables and functions */
 int EINVAL ; 
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_FANOUT_SHIFT ; 
 int calc_nnode_num (int,int) ; 
 int dbg_chk_pnode (struct ubifs_info*,struct ubifs_pnode*,int) ; 
 int /*<<< orphan*/  dbg_is_chk_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,int,int /*<<< orphan*/ ,int) ; 

int dbg_check_lpt_nodes(struct ubifs_info *c, struct ubifs_cnode *cnode,
			int row, int col)
{
	struct ubifs_nnode *nnode, *nn;
	struct ubifs_cnode *cn;
	int num, iip = 0, err;

	if (!dbg_is_chk_lprops(c))
		return 0;

	while (cnode) {
		ubifs_assert(c, row >= 0);
		nnode = cnode->parent;
		if (cnode->level) {
			/* cnode is a nnode */
			num = calc_nnode_num(row, col);
			if (cnode->num != num) {
				ubifs_err(c, "nnode num %d expected %d parent num %d iip %d",
					  cnode->num, num,
					  (nnode ? nnode->num : 0), cnode->iip);
				return -EINVAL;
			}
			nn = (struct ubifs_nnode *)cnode;
			while (iip < UBIFS_LPT_FANOUT) {
				cn = nn->nbranch[iip].cnode;
				if (cn) {
					/* Go down */
					row += 1;
					col <<= UBIFS_LPT_FANOUT_SHIFT;
					col += iip;
					iip = 0;
					cnode = cn;
					break;
				}
				/* Go right */
				iip += 1;
			}
			if (iip < UBIFS_LPT_FANOUT)
				continue;
		} else {
			struct ubifs_pnode *pnode;

			/* cnode is a pnode */
			pnode = (struct ubifs_pnode *)cnode;
			err = dbg_chk_pnode(c, pnode, col);
			if (err)
				return err;
		}
		/* Go up and to the right */
		row -= 1;
		col >>= UBIFS_LPT_FANOUT_SHIFT;
		iip = cnode->iip + 1;
		cnode = (struct ubifs_cnode *)nnode;
	}
	return 0;
}