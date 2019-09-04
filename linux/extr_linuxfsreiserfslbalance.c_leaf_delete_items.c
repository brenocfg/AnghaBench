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
struct item_head {int dummy; } ;
struct buffer_info {int /*<<< orphan*/  tb; struct buffer_head* bi_bh; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int FIRST_TO_LAST ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  do_balance_mark_leaf_dirty (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ih_entry_count (struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int) ; 
 int /*<<< orphan*/  leaf_cut_from_buffer (struct buffer_info*,int,int,int) ; 
 int /*<<< orphan*/  leaf_delete_items_entirely (struct buffer_info*,int,int) ; 
 int /*<<< orphan*/  make_empty_node (struct buffer_info*) ; 

void leaf_delete_items(struct buffer_info *cur_bi, int last_first,
		       int first, int del_num, int del_bytes)
{
	struct buffer_head *bh;
	int item_amount = B_NR_ITEMS(bh = cur_bi->bi_bh);

	RFALSE(!bh, "10155: bh is not defined");
	RFALSE(del_num < 0, "10160: del_num can not be < 0. del_num==%d",
	       del_num);
	RFALSE(first < 0
	       || first + del_num > item_amount,
	       "10165: invalid number of first item to be deleted (%d) or "
	       "no so much items (%d) to delete (only %d)", first,
	       first + del_num, item_amount);

	if (del_num == 0)
		return;

	if (first == 0 && del_num == item_amount && del_bytes == -1) {
		make_empty_node(cur_bi);
		do_balance_mark_leaf_dirty(cur_bi->tb, bh, 0);
		return;
	}

	if (del_bytes == -1)
		/* delete del_num items beginning from item in position first */
		leaf_delete_items_entirely(cur_bi, first, del_num);
	else {
		if (last_first == FIRST_TO_LAST) {
			/*
			 * delete del_num-1 items beginning from
			 * item in position first
			 */
			leaf_delete_items_entirely(cur_bi, first, del_num - 1);

			/*
			 * delete the part of the first item of the bh
			 * do not delete item header
			 */
			leaf_cut_from_buffer(cur_bi, 0, 0, del_bytes);
		} else {
			struct item_head *ih;
			int len;

			/*
			 * delete del_num-1 items beginning from
			 * item in position first+1
			 */
			leaf_delete_items_entirely(cur_bi, first + 1,
						   del_num - 1);

			ih = item_head(bh, B_NR_ITEMS(bh) - 1);
			if (is_direntry_le_ih(ih))
				/* the last item is directory  */
				/*
				 * len = numbers of directory entries
				 * in this item
				 */
				len = ih_entry_count(ih);
			else
				/* len = body len of item */
				len = ih_item_len(ih);

			/*
			 * delete the part of the last item of the bh
			 * do not delete item header
			 */
			leaf_cut_from_buffer(cur_bi, B_NR_ITEMS(bh) - 1,
					     len - del_bytes, del_bytes);
		}
	}
}