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
struct tree_balance {int* sbytes; int pos_in_item; int /*<<< orphan*/ * S_new; int /*<<< orphan*/ * snum; int /*<<< orphan*/ * insert_size; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/  item_pos; int /*<<< orphan*/  tb_path; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int DEH_SIZE ; 
 int /*<<< orphan*/  LEAF_FROM_S_TO_SNEW ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  buffer_info_init_bh (struct tree_balance*,struct buffer_info*,int /*<<< orphan*/ ) ; 
 int ih_entry_count (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_move_items (int /*<<< orphan*/ ,struct tree_balance*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,int /*<<< orphan*/ ,int,int,struct reiserfs_de_head*,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_new_nodes_paste_dirent(struct tree_balance *tb,
					 struct item_head * const ih,
					 const char * const body,
					 struct item_head *insert_key,
					 struct buffer_head **insert_ptr,
					 int i)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	struct item_head *aux_ih = item_head(tbS0, tb->item_pos);
	int entry_count = ih_entry_count(aux_ih);
	struct buffer_info bi;

	if (entry_count - tb->sbytes[i] < tb->pos_in_item &&
	    tb->pos_in_item <= entry_count) {
		/* new directory entry falls into S_new[i] */

		RFALSE(!tb->insert_size[0],
		       "PAP-12215: insert_size is already 0");
		RFALSE(tb->sbytes[i] - 1 >= entry_count,
		       "PAP-12220: there are no so much entries (%d), only %d",
		       tb->sbytes[i] - 1, entry_count);

		/*
		 * Shift snum[i]-1 items in whole.
		 * Shift sbytes[i] directory entries
		 * from directory item number snum[i]
		 */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i] - 1, tb->S_new[i]);

		/*
		 * Paste given directory entry to
		 * directory item
		 */
		buffer_info_init_bh(tb, &bi, tb->S_new[i]);
		leaf_paste_in_buffer(&bi, 0, tb->pos_in_item - entry_count +
				     tb->sbytes[i] - 1, tb->insert_size[0],
				     body, tb->zeroes_num);

		/* paste new directory entry */
		leaf_paste_entries(&bi, 0, tb->pos_in_item - entry_count +
				   tb->sbytes[i] - 1, 1,
				   (struct reiserfs_de_head *) body,
				   body + DEH_SIZE, tb->insert_size[0]);

		tb->insert_size[0] = 0;
		tb->pos_in_item++;
	} else {
		/* new directory entry doesn't fall into S_new[i] */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i], tb->S_new[i]);
	}

}