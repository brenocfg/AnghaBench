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
struct tree_balance {scalar_t__ tb_mode; int /*<<< orphan*/ * lkey; int /*<<< orphan*/ * CFL; int /*<<< orphan*/  tb_path; int /*<<< orphan*/  tb_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 scalar_t__ B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  LEAF_FROM_S_TO_L ; 
 scalar_t__ M_INSERT ; 
 scalar_t__ M_PASTE ; 
 scalar_t__ PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 struct buffer_head* PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  ih_entry_count (int /*<<< orphan*/ ) ; 
 scalar_t__ is_direntry_le_ih (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_key (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int leaf_move_items (int /*<<< orphan*/ ,struct tree_balance*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_is_left_mergeable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_cur_tb (char*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

int leaf_shift_left(struct tree_balance *tb, int shift_num, int shift_bytes)
{
	struct buffer_head *S0 = PATH_PLAST_BUFFER(tb->tb_path);
	int i;

	/*
	 * move shift_num (and shift_bytes bytes) items from S[0]
	 * to left neighbor L[0]
	 */
	i = leaf_move_items(LEAF_FROM_S_TO_L, tb, shift_num, shift_bytes, NULL);

	if (shift_num) {
		/* number of items in S[0] == 0 */
		if (B_NR_ITEMS(S0) == 0) {

			RFALSE(shift_bytes != -1,
			       "vs-10270: S0 is empty now, but shift_bytes != -1 (%d)",
			       shift_bytes);
#ifdef CONFIG_REISERFS_CHECK
			if (tb->tb_mode == M_PASTE || tb->tb_mode == M_INSERT) {
				print_cur_tb("vs-10275");
				reiserfs_panic(tb->tb_sb, "vs-10275",
					       "balance condition corrupted "
					       "(%c)", tb->tb_mode);
			}
#endif

			if (PATH_H_POSITION(tb->tb_path, 1) == 0)
				replace_key(tb, tb->CFL[0], tb->lkey[0],
					    PATH_H_PPARENT(tb->tb_path, 0), 0);

		} else {
			/* replace lkey in CFL[0] by 0-th key from S[0]; */
			replace_key(tb, tb->CFL[0], tb->lkey[0], S0, 0);

			RFALSE((shift_bytes != -1 &&
				!(is_direntry_le_ih(item_head(S0, 0))
				  && !ih_entry_count(item_head(S0, 0)))) &&
			       (!op_is_left_mergeable
				(leaf_key(S0, 0), S0->b_size)),
			       "vs-10280: item must be mergeable");
		}
	}

	return i;
}