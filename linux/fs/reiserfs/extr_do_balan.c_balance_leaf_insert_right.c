#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree_balance {int* rnum; int item_pos; int rbytes; int zeroes_num; int* insert_size; int /*<<< orphan*/ * R; int /*<<< orphan*/ * rkey; int /*<<< orphan*/ * CFR; TYPE_1__* tb_sb; int /*<<< orphan*/  tb_path; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int loff_t ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int UNFM_P_SHIFT ; 
 int /*<<< orphan*/  buffer_info_init_right (struct tree_balance*,struct buffer_info*) ; 
 int ih_item_len (struct item_head* const) ; 
 scalar_t__ is_indirect_le_ih (struct item_head* const) ; 
 int le_ih_k_offset (struct item_head* const) ; 
 int /*<<< orphan*/  leaf_insert_into_buf (struct buffer_info*,int,struct item_head* const,char const* const,int) ; 
 int /*<<< orphan*/  leaf_shift_right (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head* const,int) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head* const,int) ; 

__attribute__((used)) static void balance_leaf_insert_right(struct tree_balance *tb,
				      struct item_head * const ih,
				      const char * const body)
{

	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n = B_NR_ITEMS(tbS0);
	struct buffer_info bi;

	/* new item or part of it doesn't fall into R[0] */
	if (n - tb->rnum[0] >= tb->item_pos) {
		leaf_shift_right(tb, tb->rnum[0], tb->rbytes);
		return;
	}

	/* new item or its part falls to R[0] */

	/* part of new item falls into R[0] */
	if (tb->item_pos == n - tb->rnum[0] + 1 && tb->rbytes != -1) {
		loff_t old_key_comp, old_len, r_zeroes_number;
		const char *r_body;
		int shift;
		loff_t offset;

		leaf_shift_right(tb, tb->rnum[0] - 1, -1);

		/* Remember key component and item length */
		old_key_comp = le_ih_k_offset(ih);
		old_len = ih_item_len(ih);

		/*
		 * Calculate key component and item length to insert
		 * into R[0]
		 */
		shift = 0;
		if (is_indirect_le_ih(ih))
			shift = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
		offset = le_ih_k_offset(ih) + ((old_len - tb->rbytes) << shift);
		set_le_ih_k_offset(ih, offset);
		put_ih_item_len(ih, tb->rbytes);

		/* Insert part of the item into R[0] */
		buffer_info_init_right(tb, &bi);
		if ((old_len - tb->rbytes) > tb->zeroes_num) {
			r_zeroes_number = 0;
			r_body = body + (old_len - tb->rbytes) - tb->zeroes_num;
		} else {
			r_body = body;
			r_zeroes_number = tb->zeroes_num -
					  (old_len - tb->rbytes);
			tb->zeroes_num -= r_zeroes_number;
		}

		leaf_insert_into_buf(&bi, 0, ih, r_body, r_zeroes_number);

		/* Replace right delimiting key by first key in R[0] */
		replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

		/*
		 * Calculate key component and item length to
		 * insert into S[0]
		 */
		set_le_ih_k_offset(ih, old_key_comp);
		put_ih_item_len(ih, old_len - tb->rbytes);

		tb->insert_size[0] -= tb->rbytes;

	} else {
		/* whole new item falls into R[0] */

		/* Shift rnum[0]-1 items to R[0] */
		leaf_shift_right(tb, tb->rnum[0] - 1, tb->rbytes);

		/* Insert new item into R[0] */
		buffer_info_init_right(tb, &bi);
		leaf_insert_into_buf(&bi, tb->item_pos - n + tb->rnum[0] - 1,
				     ih, body, tb->zeroes_num);

		if (tb->item_pos - n + tb->rnum[0] - 1 == 0)
			replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

		tb->zeroes_num = tb->insert_size[0] = 0;
	}
}