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
struct super_block {int dummy; } ;

/* Variables and functions */

void print_statistics(struct super_block *s)
{

	/*
	   printk ("reiserfs_put_super: session statistics: balances %d, fix_nodes %d, \
	   bmap with search %d, without %d, dir2ind %d, ind2dir %d\n",
	   REISERFS_SB(s)->s_do_balance, REISERFS_SB(s)->s_fix_nodes,
	   REISERFS_SB(s)->s_bmaps, REISERFS_SB(s)->s_bmaps_without_search,
	   REISERFS_SB(s)->s_direct2indirect, REISERFS_SB(s)->s_indirect2direct);
	 */

}