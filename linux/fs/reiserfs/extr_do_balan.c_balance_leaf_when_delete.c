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
struct tree_balance {int* FR; int* blknum; int* rnum; scalar_t__* lnum; int /*<<< orphan*/  tb_path; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ B_LEVEL (int) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 scalar_t__ DISK_LEAF_NODE_LEVEL ; 
 int M_CUT ; 
 int M_DELETE ; 
 int /*<<< orphan*/  PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  balance_leaf_when_delete_cut (struct tree_balance*) ; 
 int /*<<< orphan*/  balance_leaf_when_delete_del (struct tree_balance*) ; 
 int balance_leaf_when_delete_left (struct tree_balance*) ; 
 int /*<<< orphan*/  buffer_info_init_tbS0 (struct tree_balance*,struct buffer_info*) ; 
 int /*<<< orphan*/  leaf_shift_right (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  reiserfs_invalidate_buffer (struct tree_balance*,struct buffer_head*) ; 

__attribute__((used)) static int balance_leaf_when_delete(struct tree_balance *tb, int flag)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	struct buffer_info bi;
	int n;

	RFALSE(tb->FR[0] && B_LEVEL(tb->FR[0]) != DISK_LEAF_NODE_LEVEL + 1,
	       "vs- 12000: level: wrong FR %z", tb->FR[0]);
	RFALSE(tb->blknum[0] > 1,
	       "PAP-12005: tb->blknum == %d, can not be > 1", tb->blknum[0]);
	RFALSE(!tb->blknum[0] && !PATH_H_PPARENT(tb->tb_path, 0),
	       "PAP-12010: tree can not be empty");

	buffer_info_init_tbS0(tb, &bi);

	/* Delete or truncate the item */

	BUG_ON(flag != M_DELETE && flag != M_CUT);
	if (flag == M_DELETE)
		balance_leaf_when_delete_del(tb);
	else /* M_CUT */
		balance_leaf_when_delete_cut(tb);


	/*
	 * the rule is that no shifting occurs unless by shifting
	 * a node can be freed
	 */
	n = B_NR_ITEMS(tbS0);


	/* L[0] takes part in balancing */
	if (tb->lnum[0])
		return balance_leaf_when_delete_left(tb);

	if (tb->rnum[0] == -1) {
		/* all contents of R[0] and S[0] will be in R[0] */
		leaf_shift_right(tb, n, -1);
		reiserfs_invalidate_buffer(tb, tbS0);
		return 0;
	}

	RFALSE(tb->rnum[0],
	       "PAP-12065: bad rnum parameter must be 0 (%d)", tb->rnum[0]);
	return 0;
}