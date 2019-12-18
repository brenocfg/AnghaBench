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
struct tree_balance {int* lkey; struct buffer_head** FL; int /*<<< orphan*/  tb_path; struct super_block* tb_sb; } ;
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_IS_IN_TREE (struct buffer_head*) ; 
 int B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  B_N_CHILD_NUM (struct buffer_head*,int) ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,struct buffer_head*,struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_find_get_block (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_left_neighbor_in_cache(struct tree_balance *tb, int h)
{
	struct buffer_head *father, *left;
	struct super_block *sb = tb->tb_sb;
	b_blocknr_t left_neighbor_blocknr;
	int left_neighbor_position;

	/* Father of the left neighbor does not exist. */
	if (!tb->FL[h])
		return 0;

	/* Calculate father of the node to be balanced. */
	father = PATH_H_PBUFFER(tb->tb_path, h + 1);

	RFALSE(!father ||
	       !B_IS_IN_TREE(father) ||
	       !B_IS_IN_TREE(tb->FL[h]) ||
	       !buffer_uptodate(father) ||
	       !buffer_uptodate(tb->FL[h]),
	       "vs-8165: F[h] (%b) or FL[h] (%b) is invalid",
	       father, tb->FL[h]);

	/*
	 * Get position of the pointer to the left neighbor
	 * into the left father.
	 */
	left_neighbor_position = (father == tb->FL[h]) ?
	    tb->lkey[h] : B_NR_ITEMS(tb->FL[h]);
	/* Get left neighbor block number. */
	left_neighbor_blocknr =
	    B_N_CHILD_NUM(tb->FL[h], left_neighbor_position);
	/* Look for the left neighbor in the cache. */
	if ((left = sb_find_get_block(sb, left_neighbor_blocknr))) {

		RFALSE(buffer_uptodate(left) && !B_IS_IN_TREE(left),
		       "vs-8170: left neighbor (%b %z) is not in the tree",
		       left, left);
		put_bh(left);
		return 1;
	}

	return 0;
}