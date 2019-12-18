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
struct super_block {int dummy; } ;
struct item_head {int dummy; } ;
struct disk_child {int dummy; } ;
struct buffer_info {scalar_t__ bi_parent; TYPE_1__* tb; int /*<<< orphan*/  bi_position; struct buffer_head* bi_bh; } ;
struct buffer_head {int b_size; int b_data; } ;
struct block_head {int dummy; } ;
struct TYPE_3__ {struct super_block* tb_sb; } ;

/* Variables and functions */
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 struct disk_child* B_N_CHILD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,int) ; 
 int blkh_free_space (struct block_head*) ; 
 int blkh_nr_item (struct block_head*) ; 
 scalar_t__ dc_size (struct disk_child*) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_balance_mark_leaf_dirty (TYPE_1__*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ih_item_len (struct item_head*) ; 
 int ih_location (struct item_head*) ; 
 int /*<<< orphan*/  is_direntry_le_ih (struct item_head*) ; 
 struct item_head* item_head (struct buffer_head*,int) ; 
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 
 int /*<<< orphan*/  memset (int,char,int) ; 
 int /*<<< orphan*/  print_cur_tb (char*) ; 
 int /*<<< orphan*/  put_dc_size (struct disk_child*,scalar_t__) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head*,int) ; 
 int /*<<< orphan*/  put_ih_location (struct item_head*,int) ; 
 int /*<<< orphan*/  reiserfs_panic (struct super_block*,char*,char*,int,int) ; 
 int /*<<< orphan*/  set_blkh_free_space (struct block_head*,int) ; 

void leaf_paste_in_buffer(struct buffer_info *bi, int affected_item_num,
			  int pos_in_item, int paste_size,
			  const char *body, int zeros_number)
{
	struct buffer_head *bh = bi->bi_bh;
	int nr, free_space;
	struct block_head *blkh;
	struct item_head *ih;
	int i;
	int last_loc, unmoved_loc;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);
	free_space = blkh_free_space(blkh);

	/* check free space */
	RFALSE(free_space < paste_size,
	       "vs-10175: not enough free space: needed %d, available %d",
	       paste_size, free_space);

#ifdef CONFIG_REISERFS_CHECK
	if (zeros_number > paste_size) {
		struct super_block *sb = NULL;
		if (bi && bi->tb)
			sb = bi->tb->tb_sb;
		print_cur_tb("10177");
		reiserfs_panic(sb, "vs-10177",
			       "zeros_number == %d, paste_size == %d",
			       zeros_number, paste_size);
	}
#endif				/* CONFIG_REISERFS_CHECK */

	/* item to be appended */
	ih = item_head(bh, affected_item_num);

	last_loc = ih_location(&ih[nr - affected_item_num - 1]);
	unmoved_loc = affected_item_num ? ih_location(ih - 1) : bh->b_size;

	/* prepare space */
	memmove(bh->b_data + last_loc - paste_size, bh->b_data + last_loc,
		unmoved_loc - last_loc);

	/* change locations */
	for (i = affected_item_num; i < nr; i++)
		put_ih_location(&ih[i - affected_item_num],
				ih_location(&ih[i - affected_item_num]) -
				paste_size);

	if (body) {
		if (!is_direntry_le_ih(ih)) {
			if (!pos_in_item) {
				/* shift data to right */
				memmove(bh->b_data + ih_location(ih) +
					paste_size,
					bh->b_data + ih_location(ih),
					ih_item_len(ih));
				/* paste data in the head of item */
				memset(bh->b_data + ih_location(ih), 0,
				       zeros_number);
				memcpy(bh->b_data + ih_location(ih) +
				       zeros_number, body,
				       paste_size - zeros_number);
			} else {
				memset(bh->b_data + unmoved_loc - paste_size, 0,
				       zeros_number);
				memcpy(bh->b_data + unmoved_loc - paste_size +
				       zeros_number, body,
				       paste_size - zeros_number);
			}
		}
	} else
		memset(bh->b_data + unmoved_loc - paste_size, '\0', paste_size);

	put_ih_item_len(ih, ih_item_len(ih) + paste_size);

	/* change free space */
	set_blkh_free_space(blkh, free_space - paste_size);

	do_balance_mark_leaf_dirty(bi->tb, bh, 0);

	if (bi->bi_parent) {
		struct disk_child *t_dc =
		    B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) + paste_size);
		do_balance_mark_internal_dirty(bi->tb, bi->bi_parent, 0);
	}
}