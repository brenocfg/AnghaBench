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
struct tree_balance {int /*<<< orphan*/  tb_path; int /*<<< orphan*/ ** FR; struct buffer_head** R; int /*<<< orphan*/ ** FL; struct buffer_head** L; } ;
struct buffer_info {struct buffer_head* bi_bh; void* bi_position; int /*<<< orphan*/ * bi_parent; struct tree_balance* tb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int FIRST_TO_LAST ; 
 int LAST_TO_FIRST ; 
#define  LEAF_FROM_L_TO_R 132 
#define  LEAF_FROM_R_TO_L 131 
#define  LEAF_FROM_S_TO_L 130 
#define  LEAF_FROM_S_TO_R 129 
#define  LEAF_FROM_S_TO_SNEW 128 
 void* PATH_H_B_ITEM_ORDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* PATH_H_PPARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,int,struct buffer_head*,struct buffer_head*) ; 
 void* get_left_neighbor_position (struct tree_balance*,int /*<<< orphan*/ ) ; 
 void* get_right_neighbor_position (struct tree_balance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct buffer_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  sb_from_bi (struct buffer_info*) ; 

__attribute__((used)) static void leaf_define_dest_src_infos(int shift_mode, struct tree_balance *tb,
				       struct buffer_info *dest_bi,
				       struct buffer_info *src_bi,
				       int *first_last,
				       struct buffer_head *Snew)
{
	memset(dest_bi, 0, sizeof(struct buffer_info));
	memset(src_bi, 0, sizeof(struct buffer_info));

	/* define dest, src, dest parent, dest position */
	switch (shift_mode) {
	case LEAF_FROM_S_TO_L:	/* it is used in leaf_shift_left */
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_PLAST_BUFFER(tb->tb_path);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, 0);

		/* src->b_item_order */
		src_bi->bi_position = PATH_H_B_ITEM_ORDER(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->L[0];
		dest_bi->bi_parent = tb->FL[0];
		dest_bi->bi_position = get_left_neighbor_position(tb, 0);
		*first_last = FIRST_TO_LAST;
		break;

	case LEAF_FROM_S_TO_R:	/* it is used in leaf_shift_right */
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_PLAST_BUFFER(tb->tb_path);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, 0);
		src_bi->bi_position = PATH_H_B_ITEM_ORDER(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->R[0];
		dest_bi->bi_parent = tb->FR[0];
		dest_bi->bi_position = get_right_neighbor_position(tb, 0);
		*first_last = LAST_TO_FIRST;
		break;

	case LEAF_FROM_R_TO_L:	/* it is used in balance_leaf_when_delete */
		src_bi->tb = tb;
		src_bi->bi_bh = tb->R[0];
		src_bi->bi_parent = tb->FR[0];
		src_bi->bi_position = get_right_neighbor_position(tb, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->L[0];
		dest_bi->bi_parent = tb->FL[0];
		dest_bi->bi_position = get_left_neighbor_position(tb, 0);
		*first_last = FIRST_TO_LAST;
		break;

	case LEAF_FROM_L_TO_R:	/* it is used in balance_leaf_when_delete */
		src_bi->tb = tb;
		src_bi->bi_bh = tb->L[0];
		src_bi->bi_parent = tb->FL[0];
		src_bi->bi_position = get_left_neighbor_position(tb, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->R[0];
		dest_bi->bi_parent = tb->FR[0];
		dest_bi->bi_position = get_right_neighbor_position(tb, 0);
		*first_last = LAST_TO_FIRST;
		break;

	case LEAF_FROM_S_TO_SNEW:
		src_bi->tb = tb;
		src_bi->bi_bh = PATH_PLAST_BUFFER(tb->tb_path);
		src_bi->bi_parent = PATH_H_PPARENT(tb->tb_path, 0);
		src_bi->bi_position = PATH_H_B_ITEM_ORDER(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = Snew;
		dest_bi->bi_parent = NULL;
		dest_bi->bi_position = 0;
		*first_last = LAST_TO_FIRST;
		break;

	default:
		reiserfs_panic(sb_from_bi(src_bi), "vs-10250",
			       "shift type is unknown (%d)", shift_mode);
	}
	RFALSE(!src_bi->bi_bh || !dest_bi->bi_bh,
	       "vs-10260: mode==%d, source (%p) or dest (%p) buffer is initialized incorrectly",
	       shift_mode, src_bi->bi_bh, dest_bi->bi_bh);
}