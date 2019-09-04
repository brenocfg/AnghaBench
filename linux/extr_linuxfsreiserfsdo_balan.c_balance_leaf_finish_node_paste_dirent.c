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
struct tree_balance {scalar_t__ pos_in_item; int /*<<< orphan*/ * insert_size; int /*<<< orphan*/ * lkey; scalar_t__* CFL; int /*<<< orphan*/ * L; int /*<<< orphan*/  item_pos; int /*<<< orphan*/  zeroes_num; int /*<<< orphan*/  tb_path; } ;
struct reiserfs_de_head {int dummy; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int DEH_SIZE ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  buffer_info_init_tbS0 (struct tree_balance*,struct buffer_info*) ; 
 scalar_t__ ih_entry_count (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_entries (struct buffer_info*,int /*<<< orphan*/ ,scalar_t__,int,struct reiserfs_de_head*,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_finish_node_paste_dirent(struct tree_balance *tb,
						  struct item_head * const ih,
						  const char * const body)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	struct item_head *pasted = item_head(tbS0, tb->item_pos);
	struct buffer_info bi;

	if (tb->pos_in_item >= 0 && tb->pos_in_item <= ih_entry_count(pasted)) {
		RFALSE(!tb->insert_size[0],
		       "PAP-12260: insert_size is 0 already");

		/* prepare space */
		buffer_info_init_tbS0(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos, tb->pos_in_item,
				     tb->insert_size[0], body, tb->zeroes_num);

		/* paste entry */
		leaf_paste_entries(&bi, tb->item_pos, tb->pos_in_item, 1,
				   (struct reiserfs_de_head *)body,
				   body + DEH_SIZE, tb->insert_size[0]);

		if (!tb->item_pos && !tb->pos_in_item) {
			RFALSE(!tb->CFL[0] || !tb->L[0],
			       "PAP-12270: CFL[0]/L[0] must  be specified");
			if (tb->CFL[0])
				replace_key(tb, tb->CFL[0], tb->lkey[0],
					    tbS0, 0);
		}

		tb->insert_size[0] = 0;
	}
}