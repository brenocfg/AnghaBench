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
struct tree_balance {int rbytes; int* insert_size; scalar_t__ pos_in_item; int zeroes_num; struct buffer_head** R; int /*<<< orphan*/ * CFR; int /*<<< orphan*/ * rkey; TYPE_1__* tb_sb; int /*<<< orphan*/ * rnum; int /*<<< orphan*/  item_pos; int /*<<< orphan*/  tb_path; } ;
struct item_head {int dummy; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 struct buffer_head* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,scalar_t__,scalar_t__) ; 
 int UNFM_P_SHIFT ; 
 int /*<<< orphan*/  add_le_key_k_offset (int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  balance_leaf_paste_right_shift_dirent (struct tree_balance*,struct item_head* const,char const* const) ; 
 int /*<<< orphan*/  buffer_info_init_right (struct tree_balance*,struct buffer_info*) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ih_item_len (int /*<<< orphan*/ ) ; 
 int ih_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_direntry_le_ih (int /*<<< orphan*/ ) ; 
 scalar_t__ is_indirect_le_ih (int /*<<< orphan*/ ) ; 
 scalar_t__ is_indirect_le_key (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_head (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_key (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaf_paste_in_buffer (struct buffer_info*,int /*<<< orphan*/ ,int,int,char const*,int) ; 
 int /*<<< orphan*/  leaf_shift_right (struct tree_balance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ih_free_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balance_leaf_paste_right_shift(struct tree_balance *tb,
				     struct item_head * const ih,
				     const char * const body)
{
	struct buffer_head *tbS0 = PATH_PLAST_BUFFER(tb->tb_path);
	int n_shift, n_rem, r_zeroes_number, version;
	unsigned long temp_rem;
	const char *r_body;
	struct buffer_info bi;

	/* we append to directory item */
	if (is_direntry_le_ih(item_head(tbS0, tb->item_pos))) {
		balance_leaf_paste_right_shift_dirent(tb, ih, body);
		return;
	}

	/* regular object */

	/*
	 * Calculate number of bytes which must be shifted
	 * from appended item
	 */
	n_shift = tb->rbytes - tb->insert_size[0];
	if (n_shift < 0)
		n_shift = 0;

	RFALSE(tb->pos_in_item != ih_item_len(item_head(tbS0, tb->item_pos)),
	       "PAP-12155: invalid position to paste. ih_item_len=%d, "
	       "pos_in_item=%d", tb->pos_in_item,
	       ih_item_len(item_head(tbS0, tb->item_pos)));

	leaf_shift_right(tb, tb->rnum[0], n_shift);

	/*
	 * Calculate number of bytes which must remain in body
	 * after appending to R[0]
	 */
	n_rem = tb->insert_size[0] - tb->rbytes;
	if (n_rem < 0)
		n_rem = 0;

	temp_rem = n_rem;

	version = ih_version(item_head(tb->R[0], 0));

	if (is_indirect_le_key(version, leaf_key(tb->R[0], 0))) {
		int shift = tb->tb_sb->s_blocksize_bits - UNFM_P_SHIFT;
		temp_rem = n_rem << shift;
	}

	add_le_key_k_offset(version, leaf_key(tb->R[0], 0), temp_rem);
	add_le_key_k_offset(version, internal_key(tb->CFR[0], tb->rkey[0]),
			    temp_rem);

	do_balance_mark_internal_dirty(tb, tb->CFR[0], 0);

	/* Append part of body into R[0] */
	buffer_info_init_right(tb, &bi);
	if (n_rem > tb->zeroes_num) {
		r_zeroes_number = 0;
		r_body = body + n_rem - tb->zeroes_num;
	} else {
		r_body = body;
		r_zeroes_number = tb->zeroes_num - n_rem;
		tb->zeroes_num -= r_zeroes_number;
	}

	leaf_paste_in_buffer(&bi, 0, n_shift, tb->insert_size[0] - n_rem,
			     r_body, r_zeroes_number);

	if (is_indirect_le_ih(item_head(tb->R[0], 0)))
		set_ih_free_space(item_head(tb->R[0], 0), 0);

	tb->insert_size[0] = n_rem;
	if (!n_rem)
		tb->pos_in_item++;
}