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
struct tree_balance {scalar_t__ item_pos; scalar_t__ s0num; } ;
struct item_head {int dummy; } ;

/* Variables and functions */
 int M_INSERT ; 
 int /*<<< orphan*/  balance_leaf_finish_node_insert (struct tree_balance*,struct item_head* const,char const* const) ; 
 int /*<<< orphan*/  balance_leaf_finish_node_paste (struct tree_balance*,struct item_head* const,char const* const) ; 

__attribute__((used)) static void balance_leaf_finish_node(struct tree_balance *tb,
				      struct item_head * const ih,
				      const char * const body, int flag)
{
	/* if we must insert or append into buffer S[0] */
	if (0 <= tb->item_pos && tb->item_pos < tb->s0num) {
		if (flag == M_INSERT)
			balance_leaf_finish_node_insert(tb, ih, body);
		else /* M_PASTE */
			balance_leaf_finish_node_paste(tb, ih, body);
	}
}