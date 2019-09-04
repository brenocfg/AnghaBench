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
struct treepath {int dummy; } ;
struct tree_balance {int* lkey; int* rkey; struct buffer_head** CFR; struct buffer_head** FR; struct buffer_head** CFL; struct buffer_head** FL; struct treepath* tb_path; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_IS_IN_TREE (struct buffer_head*) ; 
 int B_NR_ITEMS (int /*<<< orphan*/ ) ; 
 int CARRY_ON ; 
 int FIRST_PATH_ELEMENT_OFFSET ; 
 int /*<<< orphan*/  LEFT_PARENTS ; 
 int PATH_H_PATH_OFFSET (struct treepath*,int) ; 
 int /*<<< orphan*/  PATH_H_PBUFFER (struct treepath*,int) ; 
 struct buffer_head* PATH_OFFSET_PBUFFER (struct treepath*,int) ; 
 int PATH_OFFSET_POSITION (struct treepath*,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,struct buffer_head*,struct buffer_head*) ; 
 int /*<<< orphan*/  RIGHT_PARENTS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int get_far_parent (struct tree_balance*,int,struct buffer_head**,struct buffer_head**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_parents(struct tree_balance *tb, int h)
{
	struct treepath *path = tb->tb_path;
	int position,
	    ret,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h);
	struct buffer_head *curf, *curcf;

	/* Current node is the root of the tree or will be root of the tree */
	if (path_offset <= FIRST_PATH_ELEMENT_OFFSET) {
		/*
		 * The root can not have parents.
		 * Release nodes which previously were obtained as
		 * parents of the current node neighbors.
		 */
		brelse(tb->FL[h]);
		brelse(tb->CFL[h]);
		brelse(tb->FR[h]);
		brelse(tb->CFR[h]);
		tb->FL[h]  = NULL;
		tb->CFL[h] = NULL;
		tb->FR[h]  = NULL;
		tb->CFR[h] = NULL;
		return CARRY_ON;
	}

	/* Get parent FL[path_offset] of L[path_offset]. */
	position = PATH_OFFSET_POSITION(path, path_offset - 1);
	if (position) {
		/* Current node is not the first child of its parent. */
		curf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		curcf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		get_bh(curf);
		get_bh(curf);
		tb->lkey[h] = position - 1;
	} else {
		/*
		 * Calculate current parent of L[path_offset], which is the
		 * left neighbor of the current node.  Calculate current
		 * common parent of L[path_offset] and the current node.
		 * Note that CFL[path_offset] not equal FL[path_offset] and
		 * CFL[path_offset] not equal F[path_offset].
		 * Calculate lkey[path_offset].
		 */
		if ((ret = get_far_parent(tb, h + 1, &curf,
						  &curcf,
						  LEFT_PARENTS)) != CARRY_ON)
			return ret;
	}

	brelse(tb->FL[h]);
	tb->FL[h] = curf;	/* New initialization of FL[h]. */
	brelse(tb->CFL[h]);
	tb->CFL[h] = curcf;	/* New initialization of CFL[h]. */

	RFALSE((curf && !B_IS_IN_TREE(curf)) ||
	       (curcf && !B_IS_IN_TREE(curcf)),
	       "PAP-8195: FL (%b) or CFL (%b) is invalid", curf, curcf);

	/* Get parent FR[h] of R[h]. */

	/* Current node is the last child of F[h]. FR[h] != F[h]. */
	if (position == B_NR_ITEMS(PATH_H_PBUFFER(path, h + 1))) {
		/*
		 * Calculate current parent of R[h], which is the right
		 * neighbor of F[h].  Calculate current common parent of
		 * R[h] and current node. Note that CFR[h] not equal
		 * FR[path_offset] and CFR[h] not equal F[h].
		 */
		if ((ret =
		     get_far_parent(tb, h + 1, &curf, &curcf,
				    RIGHT_PARENTS)) != CARRY_ON)
			return ret;
	} else {
		/* Current node is not the last child of its parent F[h]. */
		curf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		curcf = PATH_OFFSET_PBUFFER(path, path_offset - 1);
		get_bh(curf);
		get_bh(curf);
		tb->rkey[h] = position;
	}

	brelse(tb->FR[h]);
	/* New initialization of FR[path_offset]. */
	tb->FR[h] = curf;

	brelse(tb->CFR[h]);
	/* New initialization of CFR[path_offset]. */
	tb->CFR[h] = curcf;

	RFALSE((curf && !B_IS_IN_TREE(curf)) ||
	       (curcf && !B_IS_IN_TREE(curcf)),
	       "PAP-8205: FR (%b) or CFR (%b) is invalid", curf, curcf);

	return CARRY_ON;
}