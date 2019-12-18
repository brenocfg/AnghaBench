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
struct tree_balance {scalar_t__ pos_in_item; int /*<<< orphan*/ * insert_size; int /*<<< orphan*/  tb_sb; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/  item_pos; int /*<<< orphan*/  tb_path; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  balance_leaf_finish_node_paste_dirent (struct tree_balance*,struct item_head* const,char const* const) ; 
 int /*<<< orphan*/  buffer_info_init_tbS0 (struct tree_balance*,struct buffer_info*) ; 
 scalar_t__ ih_item_len (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_cur_tb (char*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_finish_node_paste(struct tree_balance *tb,
					   struct item_head * const ih,
					   const char * const body)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	struct buffer_info bi;
	struct item_head *pasted = item_head(tbS0, tb->item_pos);

	/* when directory, may be new entry already pasted */
	if (is_direntry_le_ih(pasted)) {
		balance_leaf_finish_node_paste_dirent(tb, ih, body);
		return;
	}

	/* regular object */

	if (tb->pos_in_item == ih_item_len(pasted)) {
		RFALSE(tb->insert_size[0] <= 0,
		       "PAP-12275: insert size must not be %d",
		       tb->insert_size[0]);
		buffer_info_init_tbS0(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos,
				     tb->pos_in_item, tb->insert_size[0], body,
				     tb->zeroes_num);

		if (is_indirect_le_ih(pasted))
			set_ih_free_space(pasted, 0);

		tb->insert_size[0] = 0;
	}
#ifdef CONFIG_REISERFS_CHECK
	else if (tb->insert_size[0]) {
		print_cur_tb("12285");
		reiserfs_panic(tb->tb_sb, "PAP-12285",
		    "insert_size must be 0 (%d)", tb->insert_size[0]);
	}
#endif
}