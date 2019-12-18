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
struct ubifs_pnode {int dummy; } ;
struct ubifs_info {int lpt_first; int lpt_last; scalar_t__ nroot; int /*<<< orphan*/  main_lebs; } ;
struct ubifs_cnode {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ubifs_pnode*) ; 
 int PTR_ERR (struct ubifs_pnode*) ; 
 int /*<<< orphan*/  UBIFS_LPT_FANOUT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int dbg_check_lpt_nodes (struct ubifs_info*,struct ubifs_cnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbg_check_ltab_lnum (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  dbg_is_chk_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_lp (char*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int) ; 
 struct ubifs_pnode* ubifs_pnode_lookup (struct ubifs_info*,int) ; 

int dbg_check_ltab(struct ubifs_info *c)
{
	int lnum, err, i, cnt;

	if (!dbg_is_chk_lprops(c))
		return 0;

	/* Bring the entire tree into memory */
	cnt = DIV_ROUND_UP(c->main_lebs, UBIFS_LPT_FANOUT);
	for (i = 0; i < cnt; i++) {
		struct ubifs_pnode *pnode;

		pnode = ubifs_pnode_lookup(c, i);
		if (IS_ERR(pnode))
			return PTR_ERR(pnode);
		cond_resched();
	}

	/* Check nodes */
	err = dbg_check_lpt_nodes(c, (struct ubifs_cnode *)c->nroot, 0, 0);
	if (err)
		return err;

	/* Check each LEB */
	for (lnum = c->lpt_first; lnum <= c->lpt_last; lnum++) {
		err = dbg_check_ltab_lnum(c, lnum);
		if (err) {
			ubifs_err(c, "failed at LEB %d", lnum);
			return err;
		}
	}

	dbg_lp("succeeded");
	return 0;
}