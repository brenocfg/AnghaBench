#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int* insert_size; int /*<<< orphan*/ * lkey; scalar_t__* CFL; TYPE_1__* tb_path; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int pos_in_item; } ;

/* Variables and functions */
 int PATH_LAST_POSITION (TYPE_1__*) ; 
 struct buffer_head* PATH_PLAST_BUFFER (TYPE_1__*) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  buffer_info_init_tbS0 (struct tree_balance*,struct buffer_info*) ; 
 int /*<<< orphan*/  ih_item_len (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int) ; 
 int /*<<< orphan*/  leaf_cut_from_buffer (struct buffer_info*,int,int,int) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,scalar_t__,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_when_delete_cut(struct tree_balance *tb)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int item_pos = PATH_LAST_POSITION(tb->tb_path);
	struct item_head *ih = item_head(tbS0, item_pos);
	int pos_in_item = tb->tb_path->pos_in_item;
	struct buffer_info bi;
	buffer_info_init_tbS0(tb, &bi);

	if (is_direntry_le_ih(ih)) {
		/*
		 * UFS unlink semantics are such that you can only
		 * delete one directory entry at a time.
		 *
		 * when we cut a directory tb->insert_size[0] means
		 * number of entries to be cut (always 1)
		 */
		tb->insert_size[0] = -1;
		leaf_cut_from_buffer(&bi, item_pos, pos_in_item,
				     -tb->insert_size[0]);

		RFALSE(!item_pos && !pos_in_item && !tb->CFL[0],
		       "PAP-12030: can not change delimiting key. CFL[0]=%p",
		       tb->CFL[0]);

		if (!item_pos && !pos_in_item && tb->CFL[0])
			replace_key(tb, tb->CFL[0], tb->lkey[0], tbS0, 0);
	} else {
		leaf_cut_from_buffer(&bi, item_pos, pos_in_item,
				     -tb->insert_size[0]);

		RFALSE(!ih_item_len(ih),
		       "PAP-12035: cut must leave non-zero dynamic "
		       "length of item");
	}
}