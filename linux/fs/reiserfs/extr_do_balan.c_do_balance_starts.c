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
struct tree_balance {int /*<<< orphan*/  tb_sb; } ;
struct TYPE_2__ {struct tree_balance* cur_tb; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_before_balancing (struct tree_balance*) ; 

__attribute__((used)) static inline void do_balance_starts(struct tree_balance *tb)
{
	/* use print_cur_tb() to see initial state of struct tree_balance */

	/* store_print_tb (tb); */

	/* do not delete, just comment it out */
	/*
	print_tb(flag, PATH_LAST_POSITION(tb->tb_path),
		 tb->tb_path->pos_in_item, tb, "check");
	*/
	RFALSE(check_before_balancing(tb), "PAP-12340: locked buffers in TB");
#ifdef CONFIG_REISERFS_CHECK
	REISERFS_SB(tb->tb_sb)->cur_tb = tb;
#endif
}