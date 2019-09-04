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
struct tree_balance {int item_pos; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/ * insert_size; int /*<<< orphan*/  pos_in_item; int /*<<< orphan*/ * L; int /*<<< orphan*/  lbytes; int /*<<< orphan*/ * lnum; int /*<<< orphan*/  tb_path; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 int B_NR_ITEMS (int /*<<< orphan*/ ) ; 
 int DEH_SIZE ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_info_init_left (struct tree_balance*,struct buffer_info*) ; 
 scalar_t__ ih_entry_count (struct item_head*) ; 
 scalar_t__ ih_item_len (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 struct item_head* item_head (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  leaf_key (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,int,int /*<<< orphan*/ ,int,struct reiserfs_de_head*,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 
 int leaf_shift_left (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ op_is_left_mergeable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_paste_left_whole(struct tree_balance *tb,
					  struct item_head * const ih,
					  const char * const body)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n = B_NR_ITEMS(tb->L[0]);
	struct buffer_info bi;
	struct item_head *pasted;
	int ret;

	/* if we paste into first item of S[0] and it is left mergable */
	if (!tb->item_pos &&
	    op_is_left_mergeable(leaf_key(tbS0, 0), tbS0->b_size)) {
		/*
		 * then increment pos_in_item by the size of the
		 * last item in L[0]
		 */
		pasted = item_head(tb->L[0], n - 1);
		if (is_direntry_le_ih(pasted))
			tb->pos_in_item += ih_entry_count(pasted);
		else
			tb->pos_in_item += ih_item_len(pasted);
	}

	/*
	 * Shift lnum[0] - 1 items in whole.
	 * Shift lbytes - 1 byte from item number lnum[0]
	 */
	ret = leaf_shift_left(tb, tb->lnum[0], tb->lbytes);

	/* Append to body of item in L[0] */
	buffer_info_init_left(tb, &bi);
	leaf_paste_in_buffer(&bi, n + tb->item_pos - ret, tb->pos_in_item,
			     tb->insert_size[0], body, tb->zeroes_num);

	/* if appended item is directory, paste entry */
	pasted = item_head(tb->L[0], n + tb->item_pos - ret);
	if (is_direntry_le_ih(pasted))
		leaf_paste_entries(&bi, n + tb->item_pos - ret,
				   tb->pos_in_item, 1,
				   (struct reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

	/*
	 * if appended item is indirect item, put unformatted node
	 * into un list
	 */
	if (is_indirect_le_ih(pasted))
		set_ih_free_space(pasted, 0);

	tb->insert_size[0] = 0;
	tb->zeroes_num = 0;
}