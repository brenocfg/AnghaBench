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
struct virtual_node {int vn_nr_item; int /*<<< orphan*/  vn_mode; } ;
struct tree_balance {int* insert_size; int* rnum; int* lnum; int lbytes; int rbytes; int s0num; int /*<<< orphan*/  tb_sb; int /*<<< orphan*/  tb_path; struct virtual_node* tb_vn; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_FREE_SPACE (struct buffer_head*) ; 
#define  CARRY_ON 130 
 int /*<<< orphan*/  FLOW ; 
 int LEFT_SHIFT_FLOW ; 
 int LEFT_SHIFT_NO_FLOW ; 
 int LR_SHIFT_FLOW ; 
 int LR_SHIFT_NO_FLOW ; 
 int MAX_NR_KEY (struct buffer_head*) ; 
 int NOTHING_SHIFT_FLOW ; 
 int NOTHING_SHIFT_NO_FLOW ; 
 int NO_BALANCING_NEEDED ; 
#define  NO_DISK_SPACE 129 
 int /*<<< orphan*/  NO_FLOW ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
#define  REPEAT_SEARCH 128 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int RIGHT_SHIFT_FLOW ; 
 int RIGHT_SHIFT_NO_FLOW ; 
 int /*<<< orphan*/  SET_PAR_SHIFT_LEFT ; 
 int /*<<< orphan*/  SET_PAR_SHIFT_RIGHT ; 
 int can_node_be_removed (int /*<<< orphan*/ ,int,int,int,struct tree_balance*,int) ; 
 int /*<<< orphan*/  check_left (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  check_right (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  create_virtual_node (struct tree_balance*,int) ; 
 int get_empty_nodes (struct tree_balance*,int) ; 
 int get_lfree (struct tree_balance*,int) ; 
 int get_num_ver (int /*<<< orphan*/ ,struct tree_balance*,int,int,int,int,int,short*,int /*<<< orphan*/ ) ; 
 int get_parents (struct tree_balance*,int) ; 
 int get_rfree (struct tree_balance*,int) ; 
 scalar_t__ is_leaf_removable (struct tree_balance*) ; 
 scalar_t__ is_left_neighbor_in_cache (struct tree_balance*,int) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  set_parameters (struct tree_balance*,int,int,int,int,short*,int,int) ; 

__attribute__((used)) static int ip_check_balance(struct tree_balance *tb, int h)
{
	struct virtual_node *vn = tb->tb_vn;
	/*
	 * Number of bytes that must be inserted into (value is negative
	 * if bytes are deleted) buffer which contains node being balanced.
	 * The mnemonic is that the attempted change in node space used
	 * level is levbytes bytes.
	 */
	int levbytes;
	int ret;

	int lfree, sfree, rfree /* free space in L, S and R */ ;

	/*
	 * nver is short for number of vertixes, and lnver is the number if
	 * we shift to the left, rnver is the number if we shift to the
	 * right, and lrnver is the number if we shift in both directions.
	 * The goal is to minimize first the number of vertixes, and second,
	 * the number of vertixes whose contents are changed by shifting,
	 * and third the number of uncached vertixes whose contents are
	 * changed by shifting and must be read from disk.
	 */
	int nver, lnver, rnver, lrnver;

	/*
	 * used at leaf level only, S0 = S[0] is the node being balanced,
	 * sInum [ I = 0,1,2 ] is the number of items that will
	 * remain in node SI after balancing.  S1 and S2 are new
	 * nodes that might be created.
	 */

	/*
	 * we perform 8 calls to get_num_ver().  For each call we
	 * calculate five parameters.  where 4th parameter is s1bytes
	 * and 5th - s2bytes
	 *
	 * s0num, s1num, s2num for 8 cases
	 * 0,1 - do not shift and do not shift but bottle
	 * 2   - shift only whole item to left
	 * 3   - shift to left and bottle as much as possible
	 * 4,5 - shift to right (whole items and as much as possible
	 * 6,7 - shift to both directions (whole items and as much as possible)
	 */
	short snum012[40] = { 0, };

	/* Sh is the node whose balance is currently being checked */
	struct buffer_head *Sh;

	Sh = PATH_H_PBUFFER(tb->tb_path, h);
	levbytes = tb->insert_size[h];

	/* Calculate balance parameters for creating new root. */
	if (!Sh) {
		if (!h)
			reiserfs_panic(tb->tb_sb, "vs-8210",
				       "S[0] can not be 0");
		switch (ret = get_empty_nodes(tb, h)) {
		/* no balancing for higher levels needed */
		case CARRY_ON:
			set_parameters(tb, h, 0, 0, 1, NULL, -1, -1);
			return NO_BALANCING_NEEDED;

		case NO_DISK_SPACE:
		case REPEAT_SEARCH:
			return ret;
		default:
			reiserfs_panic(tb->tb_sb, "vs-8215", "incorrect "
				       "return value of get_empty_nodes");
		}
	}

	/* get parents of S[h] neighbors. */
	ret = get_parents(tb, h);
	if (ret != CARRY_ON)
		return ret;

	sfree = B_FREE_SPACE(Sh);

	/* get free space of neighbors */
	rfree = get_rfree(tb, h);
	lfree = get_lfree(tb, h);

	/* and new item fits into node S[h] without any shifting */
	if (can_node_be_removed(vn->vn_mode, lfree, sfree, rfree, tb, h) ==
	    NO_BALANCING_NEEDED)
		return NO_BALANCING_NEEDED;

	create_virtual_node(tb, h);

	/*
	 * determine maximal number of items we can shift to the left
	 * neighbor (in tb structure) and the maximal number of bytes
	 * that can flow to the left neighbor from the left most liquid
	 * item that cannot be shifted from S[0] entirely (returned value)
	 */
	check_left(tb, h, lfree);

	/*
	 * determine maximal number of items we can shift to the right
	 * neighbor (in tb structure) and the maximal number of bytes
	 * that can flow to the right neighbor from the right most liquid
	 * item that cannot be shifted from S[0] entirely (returned value)
	 */
	check_right(tb, h, rfree);

	/*
	 * all contents of internal node S[h] can be moved into its
	 * neighbors, S[h] will be removed after balancing
	 */
	if (h && (tb->rnum[h] + tb->lnum[h] >= vn->vn_nr_item + 1)) {
		int to_r;

		/*
		 * Since we are working on internal nodes, and our internal
		 * nodes have fixed size entries, then we can balance by the
		 * number of items rather than the space they consume.  In this
		 * routine we set the left node equal to the right node,
		 * allowing a difference of less than or equal to 1 child
		 * pointer.
		 */
		to_r =
		    ((MAX_NR_KEY(Sh) << 1) + 2 - tb->lnum[h] - tb->rnum[h] +
		     vn->vn_nr_item + 1) / 2 - (MAX_NR_KEY(Sh) + 1 -
						tb->rnum[h]);
		set_parameters(tb, h, vn->vn_nr_item + 1 - to_r, to_r, 0, NULL,
			       -1, -1);
		return CARRY_ON;
	}

	/*
	 * this checks balance condition, that any two neighboring nodes
	 * can not fit in one node
	 */
	RFALSE(h &&
	       (tb->lnum[h] >= vn->vn_nr_item + 1 ||
		tb->rnum[h] >= vn->vn_nr_item + 1),
	       "vs-8220: tree is not balanced on internal level");
	RFALSE(!h && ((tb->lnum[h] >= vn->vn_nr_item && (tb->lbytes == -1)) ||
		      (tb->rnum[h] >= vn->vn_nr_item && (tb->rbytes == -1))),
	       "vs-8225: tree is not balanced on leaf level");

	/*
	 * all contents of S[0] can be moved into its neighbors
	 * S[0] will be removed after balancing.
	 */
	if (!h && is_leaf_removable(tb))
		return CARRY_ON;

	/*
	 * why do we perform this check here rather than earlier??
	 * Answer: we can win 1 node in some cases above. Moreover we
	 * checked it above, when we checked, that S[0] is not removable
	 * in principle
	 */

	 /* new item fits into node S[h] without any shifting */
	if (sfree >= levbytes) {
		if (!h)
			tb->s0num = vn->vn_nr_item;
		set_parameters(tb, h, 0, 0, 1, NULL, -1, -1);
		return NO_BALANCING_NEEDED;
	}

	{
		int lpar, rpar, nset, lset, rset, lrset;
		/* regular overflowing of the node */

		/*
		 * get_num_ver works in 2 modes (FLOW & NO_FLOW)
		 * lpar, rpar - number of items we can shift to left/right
		 *              neighbor (including splitting item)
		 * nset, lset, rset, lrset - shows, whether flowing items
		 *                           give better packing
		 */
#define FLOW 1
#define NO_FLOW 0		/* do not any splitting */

		/* we choose one of the following */
#define NOTHING_SHIFT_NO_FLOW	0
#define NOTHING_SHIFT_FLOW	5
#define LEFT_SHIFT_NO_FLOW	10
#define LEFT_SHIFT_FLOW		15
#define RIGHT_SHIFT_NO_FLOW	20
#define RIGHT_SHIFT_FLOW	25
#define LR_SHIFT_NO_FLOW	30
#define LR_SHIFT_FLOW		35

		lpar = tb->lnum[h];
		rpar = tb->rnum[h];

		/*
		 * calculate number of blocks S[h] must be split into when
		 * nothing is shifted to the neighbors, as well as number of
		 * items in each part of the split node (s012 numbers),
		 * and number of bytes (s1bytes) of the shared drop which
		 * flow to S1 if any
		 */
		nset = NOTHING_SHIFT_NO_FLOW;
		nver = get_num_ver(vn->vn_mode, tb, h,
				   0, -1, h ? vn->vn_nr_item : 0, -1,
				   snum012, NO_FLOW);

		if (!h) {
			int nver1;

			/*
			 * note, that in this case we try to bottle
			 * between S[0] and S1 (S1 - the first new node)
			 */
			nver1 = get_num_ver(vn->vn_mode, tb, h,
					    0, -1, 0, -1,
					    snum012 + NOTHING_SHIFT_FLOW, FLOW);
			if (nver > nver1)
				nset = NOTHING_SHIFT_FLOW, nver = nver1;
		}

		/*
		 * calculate number of blocks S[h] must be split into when
		 * l_shift_num first items and l_shift_bytes of the right
		 * most liquid item to be shifted are shifted to the left
		 * neighbor, as well as number of items in each part of the
		 * splitted node (s012 numbers), and number of bytes
		 * (s1bytes) of the shared drop which flow to S1 if any
		 */
		lset = LEFT_SHIFT_NO_FLOW;
		lnver = get_num_ver(vn->vn_mode, tb, h,
				    lpar - ((h || tb->lbytes == -1) ? 0 : 1),
				    -1, h ? vn->vn_nr_item : 0, -1,
				    snum012 + LEFT_SHIFT_NO_FLOW, NO_FLOW);
		if (!h) {
			int lnver1;

			lnver1 = get_num_ver(vn->vn_mode, tb, h,
					     lpar -
					     ((tb->lbytes != -1) ? 1 : 0),
					     tb->lbytes, 0, -1,
					     snum012 + LEFT_SHIFT_FLOW, FLOW);
			if (lnver > lnver1)
				lset = LEFT_SHIFT_FLOW, lnver = lnver1;
		}

		/*
		 * calculate number of blocks S[h] must be split into when
		 * r_shift_num first items and r_shift_bytes of the left most
		 * liquid item to be shifted are shifted to the right neighbor,
		 * as well as number of items in each part of the splitted
		 * node (s012 numbers), and number of bytes (s1bytes) of the
		 * shared drop which flow to S1 if any
		 */
		rset = RIGHT_SHIFT_NO_FLOW;
		rnver = get_num_ver(vn->vn_mode, tb, h,
				    0, -1,
				    h ? (vn->vn_nr_item - rpar) : (rpar -
								   ((tb->
								     rbytes !=
								     -1) ? 1 :
								    0)), -1,
				    snum012 + RIGHT_SHIFT_NO_FLOW, NO_FLOW);
		if (!h) {
			int rnver1;

			rnver1 = get_num_ver(vn->vn_mode, tb, h,
					     0, -1,
					     (rpar -
					      ((tb->rbytes != -1) ? 1 : 0)),
					     tb->rbytes,
					     snum012 + RIGHT_SHIFT_FLOW, FLOW);

			if (rnver > rnver1)
				rset = RIGHT_SHIFT_FLOW, rnver = rnver1;
		}

		/*
		 * calculate number of blocks S[h] must be split into when
		 * items are shifted in both directions, as well as number
		 * of items in each part of the splitted node (s012 numbers),
		 * and number of bytes (s1bytes) of the shared drop which
		 * flow to S1 if any
		 */
		lrset = LR_SHIFT_NO_FLOW;
		lrnver = get_num_ver(vn->vn_mode, tb, h,
				     lpar - ((h || tb->lbytes == -1) ? 0 : 1),
				     -1,
				     h ? (vn->vn_nr_item - rpar) : (rpar -
								    ((tb->
								      rbytes !=
								      -1) ? 1 :
								     0)), -1,
				     snum012 + LR_SHIFT_NO_FLOW, NO_FLOW);
		if (!h) {
			int lrnver1;

			lrnver1 = get_num_ver(vn->vn_mode, tb, h,
					      lpar -
					      ((tb->lbytes != -1) ? 1 : 0),
					      tb->lbytes,
					      (rpar -
					       ((tb->rbytes != -1) ? 1 : 0)),
					      tb->rbytes,
					      snum012 + LR_SHIFT_FLOW, FLOW);
			if (lrnver > lrnver1)
				lrset = LR_SHIFT_FLOW, lrnver = lrnver1;
		}

		/*
		 * Our general shifting strategy is:
		 * 1) to minimized number of new nodes;
		 * 2) to minimized number of neighbors involved in shifting;
		 * 3) to minimized number of disk reads;
		 */

		/* we can win TWO or ONE nodes by shifting in both directions */
		if (lrnver < lnver && lrnver < rnver) {
			RFALSE(h &&
			       (tb->lnum[h] != 1 ||
				tb->rnum[h] != 1 ||
				lrnver != 1 || rnver != 2 || lnver != 2
				|| h != 1), "vs-8230: bad h");
			if (lrset == LR_SHIFT_FLOW)
				set_parameters(tb, h, tb->lnum[h], tb->rnum[h],
					       lrnver, snum012 + lrset,
					       tb->lbytes, tb->rbytes);
			else
				set_parameters(tb, h,
					       tb->lnum[h] -
					       ((tb->lbytes == -1) ? 0 : 1),
					       tb->rnum[h] -
					       ((tb->rbytes == -1) ? 0 : 1),
					       lrnver, snum012 + lrset, -1, -1);

			return CARRY_ON;
		}

		/*
		 * if shifting doesn't lead to better packing
		 * then don't shift
		 */
		if (nver == lrnver) {
			set_parameters(tb, h, 0, 0, nver, snum012 + nset, -1,
				       -1);
			return CARRY_ON;
		}

		/*
		 * now we know that for better packing shifting in only one
		 * direction either to the left or to the right is required
		 */

		/*
		 * if shifting to the left is better than
		 * shifting to the right
		 */
		if (lnver < rnver) {
			SET_PAR_SHIFT_LEFT;
			return CARRY_ON;
		}

		/*
		 * if shifting to the right is better than
		 * shifting to the left
		 */
		if (lnver > rnver) {
			SET_PAR_SHIFT_RIGHT;
			return CARRY_ON;
		}

		/*
		 * now shifting in either direction gives the same number
		 * of nodes and we can make use of the cached neighbors
		 */
		if (is_left_neighbor_in_cache(tb, h)) {
			SET_PAR_SHIFT_LEFT;
			return CARRY_ON;
		}

		/*
		 * shift to the right independently on whether the
		 * right neighbor in cache or not
		 */
		SET_PAR_SHIFT_RIGHT;
		return CARRY_ON;
	}
}