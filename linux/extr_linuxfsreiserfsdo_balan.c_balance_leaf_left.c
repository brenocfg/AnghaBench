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
struct tree_balance {scalar_t__* lnum; scalar_t__ item_pos; int /*<<< orphan*/  lbytes; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int M_INSERT ; 
 int M_PASTE ; 
 unsigned int balance_leaf_insert_left (struct tree_balance*,struct item_head* const,char const* const) ; 
 unsigned int balance_leaf_paste_left (struct tree_balance*,struct item_head* const,char const* const) ; 
 int /*<<< orphan*/  leaf_shift_left (struct tree_balance*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int balance_leaf_left(struct tree_balance *tb,
				      struct item_head * const ih,
				      const char * const body, int flag)
{
	if (tb->lnum[0] <= 0)
		return 0;

	/* new item or it part falls to L[0], shift it too */
	if (tb->item_pos < tb->lnum[0]) {
		BUG_ON(flag != M_INSERT && flag != M_PASTE);

		if (flag == M_INSERT)
			return balance_leaf_insert_left(tb, ih, body);
		else /* M_PASTE */
			return balance_leaf_paste_left(tb, ih, body);
	} else
		/* new item doesn't fall into L[0] */
		leaf_shift_left(tb, tb->lnum[0], tb->lbytes);
	return 0;
}