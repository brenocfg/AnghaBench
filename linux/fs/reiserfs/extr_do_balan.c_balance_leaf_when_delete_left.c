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
struct tree_balance {int* lnum; int* rnum; int lbytes; int rbytes; struct buffer_head** L; struct buffer_head** R; int /*<<< orphan*/ * rkey; int /*<<< orphan*/ * CFR; struct buffer_head** FR; int /*<<< orphan*/ * lkey; int /*<<< orphan*/ * CFL; int /*<<< orphan*/  tb_path; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  LEAF_FROM_L_TO_R ; 
 int /*<<< orphan*/  LEAF_FROM_R_TO_L ; 
 int /*<<< orphan*/  LEAF_FROM_S_TO_L ; 
 int /*<<< orphan*/  LEAF_FROM_S_TO_R ; 
 scalar_t__ PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 struct buffer_head* PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,...) ; 
 int /*<<< orphan*/  leaf_move_items (int /*<<< orphan*/ ,struct tree_balance*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leaf_shift_left (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  leaf_shift_right (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  reiserfs_invalidate_buffer (struct tree_balance*,struct buffer_head*) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*,int) ; 

__attribute__((used)) static int balance_leaf_when_delete_left(struct tree_balance *tb)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n = B_NR_ITEMS(tbS0);

	/* L[0] must be joined with S[0] */
	if (tb->lnum[0] == -1) {
		/* R[0] must be also joined with S[0] */
		if (tb->rnum[0] == -1) {
			if (tb->FR[0] == PATH_H_PPARENT(tb->tb_path, 0)) {
				/*
				 * all contents of all the
				 * 3 buffers will be in L[0]
				 */
				if (PATH_H_POSITION(tb->tb_path, 1) == 0 &&
				    1 < B_NR_ITEMS(tb->FR[0]))
					replace_key(tb, tb->CFL[0],
						    tb->lkey[0], tb->FR[0], 1);

				leaf_move_items(LEAF_FROM_S_TO_L, tb, n, -1,
						NULL);
				leaf_move_items(LEAF_FROM_R_TO_L, tb,
						B_NR_ITEMS(tb->R[0]), -1,
						NULL);

				reiserfs_invalidate_buffer(tb, tbS0);
				reiserfs_invalidate_buffer(tb, tb->R[0]);

				return 0;
			}

			/* all contents of all the 3 buffers will be in R[0] */
			leaf_move_items(LEAF_FROM_S_TO_R, tb, n, -1, NULL);
			leaf_move_items(LEAF_FROM_L_TO_R, tb,
					B_NR_ITEMS(tb->L[0]), -1, NULL);

			/* right_delimiting_key is correct in R[0] */
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

			reiserfs_invalidate_buffer(tb, tbS0);
			reiserfs_invalidate_buffer(tb, tb->L[0]);

			return -1;
		}

		RFALSE(tb->rnum[0] != 0,
		       "PAP-12045: rnum must be 0 (%d)", tb->rnum[0]);
		/* all contents of L[0] and S[0] will be in L[0] */
		leaf_shift_left(tb, n, -1);

		reiserfs_invalidate_buffer(tb, tbS0);

		return 0;
	}

	/*
	 * a part of contents of S[0] will be in L[0] and
	 * the rest part of S[0] will be in R[0]
	 */

	RFALSE((tb->lnum[0] + tb->rnum[0] < n) ||
	       (tb->lnum[0] + tb->rnum[0] > n + 1),
	       "PAP-12050: rnum(%d) and lnum(%d) and item "
	       "number(%d) in S[0] are not consistent",
	       tb->rnum[0], tb->lnum[0], n);
	RFALSE((tb->lnum[0] + tb->rnum[0] == n) &&
	       (tb->lbytes != -1 || tb->rbytes != -1),
	       "PAP-12055: bad rbytes (%d)/lbytes (%d) "
	       "parameters when items are not split",
	       tb->rbytes, tb->lbytes);
	RFALSE((tb->lnum[0] + tb->rnum[0] == n + 1) &&
	       (tb->lbytes < 1 || tb->rbytes != -1),
	       "PAP-12060: bad rbytes (%d)/lbytes (%d) "
	       "parameters when items are split",
	       tb->rbytes, tb->lbytes);

	leaf_shift_left(tb, tb->lnum[0], tb->lbytes);
	leaf_shift_right(tb, tb->rnum[0], tb->rbytes);

	reiserfs_invalidate_buffer(tb, tbS0);

	return 0;
}