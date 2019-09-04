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
struct tree_balance {int /*<<< orphan*/ * L; int /*<<< orphan*/ * CFL; int /*<<< orphan*/  tb_path; int /*<<< orphan*/ * lkey; int /*<<< orphan*/ * insert_size; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  IH_SIZE ; 
 int /*<<< orphan*/  PATH_H_POSITION (int /*<<< orphan*/ ,int) ; 
 struct buffer_head* PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PATH_LAST_POSITION (int /*<<< orphan*/ ) ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_info_init_tbS0 (struct tree_balance*,struct buffer_info*) ; 
 int /*<<< orphan*/  ih ; 
 int /*<<< orphan*/  ih_item_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_delete_items (struct buffer_info*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_when_delete_del(struct tree_balance *tb)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int item_pos = PATH_LAST_POSITION(tb->tb_path);
	struct buffer_info bi;
#ifdef CONFIG_REISERFS_CHECK
	struct item_head *ih = item_head(tbS0, item_pos);
#endif

	RFALSE(ih_item_len(ih) + IH_SIZE != -tb->insert_size[0],
	       "vs-12013: mode Delete, insert size %d, ih to be deleted %h",
	       -tb->insert_size[0], ih);

	buffer_info_init_tbS0(tb, &bi);
	leaf_delete_items(&bi, 0, item_pos, 1, -1);

	if (!item_pos && tb->CFL[0]) {
		if (B_NR_ITEMS(tbS0)) {
			replace_key(tb, tb->CFL[0], tb->lkey[0], tbS0, 0);
		} else {
			if (!PATH_H_POSITION(tb->tb_path, 1))
				replace_key(tb, tb->CFL[0], tb->lkey[0],
					    PATH_H_PPARENT(tb->tb_path, 0), 0);
		}
	}

	RFALSE(!item_pos && !tb->CFL[0],
	       "PAP-12020: tb->CFL[0]==%p, tb->L[0]==%p", tb->CFL[0],
	       tb->L[0]);
}