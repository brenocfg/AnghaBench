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
struct tree_balance {int lbytes; int pos_in_item; int /*<<< orphan*/ * lnum; int /*<<< orphan*/ * insert_size; scalar_t__ item_pos; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/ * L; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (int /*<<< orphan*/ ) ; 
 int DEH_SIZE ; 
 int /*<<< orphan*/  RFALSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  buffer_info_init_left (struct tree_balance*,struct buffer_info*) ; 
 int ih_entry_count (struct item_head*) ; 
 struct item_head* item_head (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,scalar_t__,int,int,struct reiserfs_de_head*,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,scalar_t__,int,int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 
 int leaf_shift_left (struct tree_balance*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void balance_leaf_paste_left_shift_dirent(struct tree_balance *tb,
						 struct item_head * const ih,
						 const char * const body)
{
	int n = B_NR_ITEMS(tb->L[0]);
	struct buffer_info bi;

	RFALSE(tb->zeroes_num,
	       "PAP-12090: invalid parameter in case of a directory");

	/* directory item */
	if (tb->lbytes > tb->pos_in_item) {
		/* new directory entry falls into L[0] */
		struct item_head *pasted;
		int ret, l_pos_in_item = tb->pos_in_item;

		/*
		 * Shift lnum[0] - 1 items in whole.
		 * Shift lbytes - 1 entries from given directory item
		 */
		ret = leaf_shift_left(tb, tb->lnum[0], tb->lbytes - 1);
		if (ret && !tb->item_pos) {
			pasted = item_head(tb->L[0], B_NR_ITEMS(tb->L[0]) - 1);
			l_pos_in_item += ih_entry_count(pasted) -
					 (tb->lbytes - 1);
		}

		/* Append given directory entry to directory item */
		buffer_info_init_left(tb, &bi);
		leaf_paste_in_buffer(&bi, n + tb->item_pos - ret,
				     l_pos_in_item, tb->insert_size[0],
				     body, tb->zeroes_num);

		/*
		 * previous string prepared space for pasting new entry,
		 * following string pastes this entry
		 */

		/*
		 * when we have merge directory item, pos_in_item
		 * has been changed too
		 */

		/* paste new directory entry. 1 is entry number */
		leaf_paste_entries(&bi, n + tb->item_pos - ret,
				   l_pos_in_item, 1,
				   (struct reiserfs_de_head *) body,
				   body + DEH_SIZE, tb->insert_size[0]);
		tb->insert_size[0] = 0;
	} else {
		/* new directory item doesn't fall into L[0] */
		/*
		 * Shift lnum[0]-1 items in whole. Shift lbytes
		 * directory entries from directory item number lnum[0]
		 */
		leaf_shift_left(tb, tb->lnum[0], tb->lbytes);
	}

	/* Calculate new position to append in item body */
	tb->pos_in_item -= tb->lbytes;
}