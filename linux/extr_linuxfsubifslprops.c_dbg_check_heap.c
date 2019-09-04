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
struct ubifs_lpt_heap {int cnt; struct ubifs_lprops** arr; } ;
struct ubifs_lprops {int flags; int hpos; scalar_t__ lnum; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_lprops*) ; 
 int LPROPS_CAT_MASK ; 
 int /*<<< orphan*/  dbg_is_chk_gen (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_is_chk_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubifs_dump_heap (struct ubifs_info*,struct ubifs_lpt_heap*,int) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,int,int,int,...) ; 
 struct ubifs_lprops* ubifs_lpt_lookup (struct ubifs_info*,scalar_t__) ; 

void dbg_check_heap(struct ubifs_info *c, struct ubifs_lpt_heap *heap, int cat,
		    int add_pos)
{
	int i = 0, j, err = 0;

	if (!dbg_is_chk_gen(c) && !dbg_is_chk_lprops(c))
		return;

	for (i = 0; i < heap->cnt; i++) {
		struct ubifs_lprops *lprops = heap->arr[i];
		struct ubifs_lprops *lp;

		if (i != add_pos)
			if ((lprops->flags & LPROPS_CAT_MASK) != cat) {
				err = 1;
				goto out;
			}
		if (lprops->hpos != i) {
			err = 2;
			goto out;
		}
		lp = ubifs_lpt_lookup(c, lprops->lnum);
		if (IS_ERR(lp)) {
			err = 3;
			goto out;
		}
		if (lprops != lp) {
			ubifs_err(c, "lprops %zx lp %zx lprops->lnum %d lp->lnum %d",
				  (size_t)lprops, (size_t)lp, lprops->lnum,
				  lp->lnum);
			err = 4;
			goto out;
		}
		for (j = 0; j < i; j++) {
			lp = heap->arr[j];
			if (lp == lprops) {
				err = 5;
				goto out;
			}
			if (lp->lnum == lprops->lnum) {
				err = 6;
				goto out;
			}
		}
	}
out:
	if (err) {
		ubifs_err(c, "failed cat %d hpos %d err %d", cat, i, err);
		dump_stack();
		ubifs_dump_heap(c, heap, cat);
	}
}