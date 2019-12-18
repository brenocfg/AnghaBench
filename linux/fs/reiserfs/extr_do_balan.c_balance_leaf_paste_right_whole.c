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
struct tree_balance {int* rnum; scalar_t__ pos_in_item; int item_pos; int /*<<< orphan*/ * insert_size; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/ * R; int /*<<< orphan*/ * rkey; int /*<<< orphan*/ * CFR; int /*<<< orphan*/  rbytes; int /*<<< orphan*/  tb_path; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int DEH_SIZE ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  buffer_info_init_right (struct tree_balance*,struct buffer_info*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 struct item_head* item_head (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,int,scalar_t__,int,struct reiserfs_de_head*,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int,scalar_t__,int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_shift_right (struct tree_balance*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_paste_right_whole(struct tree_balance *tb,
				     struct item_head * const ih,
				     const char * const body)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n = B_NR_ITEMS(tbS0);
	struct item_head *pasted;
	struct buffer_info bi;

							buffer_info_init_right(tb, &bi);
	leaf_shift_right(tb, tb->rnum[0], tb->rbytes);

	/* append item in R[0] */
	if (tb->pos_in_item >= 0) {
		buffer_info_init_right(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos - n + tb->rnum[0],
				     tb->pos_in_item, tb->insert_size[0], body,
				     tb->zeroes_num);
	}

	/* paste new entry, if item is directory item */
	pasted = item_head(tb->R[0], tb->item_pos - n + tb->rnum[0]);
	if (is_direntry_le_ih(pasted) && tb->pos_in_item >= 0) {
		leaf_paste_entries(&bi, tb->item_pos - n + tb->rnum[0],
				   tb->pos_in_item, 1,
				   (struct reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

		if (!tb->pos_in_item) {

			RFALSE(tb->item_pos - n + tb->rnum[0],
			       "PAP-12165: directory item must be first "
			       "item of node when pasting is in 0th position");

			/* update delimiting keys */
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);
		}
	}

	if (is_indirect_le_ih(pasted))
		set_ih_free_space(pasted, 0);
	tb->zeroes_num = tb->insert_size[0] = 0;
}