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
struct tree_balance {scalar_t__* rnum; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int M_INSERT ; 
 int M_PASTE ; 
 int /*<<< orphan*/  balance_leaf_insert_right (struct tree_balance*,struct item_head* const,char const* const) ; 
 int /*<<< orphan*/  balance_leaf_paste_right (struct tree_balance*,struct item_head* const,char const* const) ; 

__attribute__((used)) static void balance_leaf_right(struct tree_balance *tb,
			       struct item_head * const ih,
			       const char * const body, int flag)
{
	if (tb->rnum[0] <= 0)
		return;

	BUG_ON(flag != M_INSERT && flag != M_PASTE);

	if (flag == M_INSERT)
		balance_leaf_insert_right(tb, ih, body);
	else /* M_PASTE */
		balance_leaf_paste_right(tb, ih, body);
}