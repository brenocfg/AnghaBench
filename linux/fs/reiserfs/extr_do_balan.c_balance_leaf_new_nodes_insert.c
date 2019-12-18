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
struct tree_balance {int* snum; int item_pos; int* sbytes; int zeroes_num; int* insert_size; int /*<<< orphan*/ * S_new; TYPE_1__* tb_sb; int /*<<< orphan*/  tb_path; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  LEAF_FROM_S_TO_SNEW ; 
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int UNFM_P_SHIFT ; 
 int /*<<< orphan*/  buffer_info_init_bh (struct tree_balance*,struct buffer_info*,int /*<<< orphan*/ ) ; 
 int ih_item_len (struct item_head* const) ; 
 scalar_t__ is_indirect_le_ih (struct item_head* const) ; 
 int le_ih_k_offset (struct item_head* const) ; 
 int /*<<< orphan*/  leaf_insert_into_buf (struct buffer_info*,int,struct item_head* const,char const* const,int) ; 
 int /*<<< orphan*/  leaf_move_items (int /*<<< orphan*/ ,struct tree_balance*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head* const,int) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head* const,int) ; 

__attribute__((used)) static void balance_leaf_new_nodes_insert(struct tree_balance *tb,
					  struct item_head * const ih,
					  const char * const body,
					  struct item_head *insert_key,
					  struct buffer_head **insert_ptr,
					  int i)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n = B_NR_ITEMS(tbS0);
	struct buffer_info bi;
	int shift;

	/* new item or it part don't falls into S_new[i] */
	if (n - tb->snum[i] >= tb->item_pos) {
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb,
				tb->snum[i], tb->sbytes[i], tb->S_new[i]);
		return;
	}

	/* new item or it's part falls to first new node S_new[i] */

	/* part of new item falls into S_new[i] */
	if (tb->item_pos == n - tb->snum[i] + 1 && tb->sbytes[i] != -1) {
		int old_key_comp, old_len, r_zeroes_number;
		const char *r_body;

		/* Move snum[i]-1 items from S[0] to S_new[i] */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb, tb->snum[i] - 1, -1,
				tb->S_new[i]);

		/* Remember key component and item length */
		old_key_comp = le_ih_k_offset(ih);
		old_len = ih_item_len(ih);

		/*
		 * Calculate key component and item length to insert
		 * into S_new[i]
		 */
		shift = 0;
		if (is_indirect_le_ih(ih))
			shift = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
		set_le_ih_k_offset(ih,
				   le_ih_k_offset(ih) +
				   ((old_len - tb->sbytes[i]) << shift));

		put_ih_item_len(ih, tb->sbytes[i]);

		/* Insert part of the item into S_new[i] before 0-th item */
		buffer_info_init_bh(tb, &bi, tb->S_new[i]);

		if ((old_len - tb->sbytes[i]) > tb->zeroes_num) {
			r_zeroes_number = 0;
			r_body = body + (old_len - tb->sbytes[i]) -
					 tb->zeroes_num;
		} else {
			r_body = body;
			r_zeroes_number = tb->zeroes_num - (old_len -
					  tb->sbytes[i]);
			tb->zeroes_num -= r_zeroes_number;
		}

		leaf_insert_into_buf(&bi, 0, ih, r_body, r_zeroes_number);

		/*
		 * Calculate key component and item length to
		 * insert into S[i]
		 */
		set_le_ih_k_offset(ih, old_key_comp);
		put_ih_item_len(ih, old_len - tb->sbytes[i]);
		tb->insert_size[0] -= tb->sbytes[i];
	} else {
		/* whole new item falls into S_new[i] */

		/*
		 * Shift snum[0] - 1 items to S_new[i]
		 * (sbytes[i] of split item)
		 */
		leaf_move_items(LEAF_FROM_S_TO_SNEW, tb,
				tb->snum[i] - 1, tb->sbytes[i], tb->S_new[i]);

		/* Insert new item into S_new[i] */
		buffer_info_init_bh(tb, &bi, tb->S_new[i]);
		leaf_insert_into_buf(&bi, tb->item_pos - n + tb->snum[i] - 1,
				     ih, body, tb->zeroes_num);

		tb->zeroes_num = tb->insert_size[0] = 0;
	}
}