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
struct tree_balance {int item_pos; scalar_t__ pos_in_item; scalar_t__* insert_size; int* snum; scalar_t__ zeroes_num; struct buffer_head** S_new; int /*<<< orphan*/ * sbytes; int /*<<< orphan*/  tb_sb; int /*<<< orphan*/  tb_path; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int DEH_SIZE ; 
 int /*<<< orphan*/  LEAF_FROM_S_TO_SNEW ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int) ; 
 int /*<<< orphan*/  buffer_info_init_bh (struct tree_balance*,struct buffer_info*,struct buffer_head*) ; 
 scalar_t__ ih_item_len (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int) ; 
 int leaf_move_items (int /*<<< orphan*/ ,struct tree_balance*,int,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,int,scalar_t__,int,struct reiserfs_de_head*,char const* const,scalar_t__) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int,scalar_t__,scalar_t__,char const* const,scalar_t__) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_new_nodes_paste_whole(struct tree_balance *tb,
					       struct item_head * const ih,
					       const char * const body,
					       struct item_head *insert_key,
					       struct buffer_head **insert_ptr,
					       int i)

{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n = B_NR_ITEMS(tbS0);
	int leaf_mi;
	struct item_head *pasted;
	struct buffer_info bi;

#ifdef CONFIG_REISERFS_CHECK
	struct item_head *ih_check = item_head(tbS0, tb->item_pos);

	if (!is_direntry_le_ih(ih_check) &&
	    (tb->pos_in_item != ih_item_len(ih_check) ||
	    tb->insert_size[0] <= 0))
		reiserfs_panic(tb->tb_sb,
			     "PAP-12235",
			     "pos_in_item must be equal to ih_item_len");
#endif

	leaf_mi = leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				  tb->sbytes[i], tb->S_new[i]);

	RFALSE(leaf_mi,
	       "PAP-12240: unexpected value returned by leaf_move_items (%d)",
	       leaf_mi);

	/* paste into item */
	buffer_info_init_bh(tb, &bi, tb->S_new[i]);
	leaf_paste_in_buffer(&bi, tb->item_pos - n + tb->snum[i],
			     tb->pos_in_item, tb->insert_size[0],
			     body, tb->zeroes_num);

	pasted = item_head(tb->S_new[i], tb->item_pos - n +
			   tb->snum[i]);
	if (is_direntry_le_ih(pasted))
		leaf_paste_entries(&bi, tb->item_pos - n + tb->snum[i],
				   tb->pos_in_item, 1,
				   (struct reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

	/* if we paste to indirect item update ih_free_space */
	if (is_indirect_le_ih(pasted))
		set_ih_free_space(pasted, 0);

	tb->zeroes_num = tb->insert_size[0] = 0;

}