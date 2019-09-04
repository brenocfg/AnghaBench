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
struct tree_balance {int /*<<< orphan*/  transaction_handle; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  journal_mark_dirty (int /*<<< orphan*/ ,struct buffer_head*) ; 

inline void do_balance_mark_leaf_dirty(struct tree_balance *tb,
				       struct buffer_head *bh, int flag)
{
	journal_mark_dirty(tb->transaction_handle, bh);
}