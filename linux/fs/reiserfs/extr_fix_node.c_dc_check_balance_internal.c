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
struct virtual_node {int vn_nr_item; } ;
struct tree_balance {int* lnum; int* rnum; struct buffer_head** FR; struct buffer_head** FL; int /*<<< orphan*/  tb_path; struct virtual_node* tb_vn; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  B_N_CHILD (struct buffer_head*,int) ; 
 int CARRY_ON ; 
 int DC_SIZE ; 
 int KEY_SIZE ; 
 int MAX_NR_KEY (struct buffer_head*) ; 
 int MIN_NR_KEY (struct buffer_head*) ; 
 int NO_BALANCING_NEEDED ; 
 int PATH_H_B_ITEM_ORDER (int /*<<< orphan*/ ,int) ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int) ; 
 struct buffer_head* PATH_H_PPARENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*) ; 
 int /*<<< orphan*/  check_left (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  check_right (struct tree_balance*,int,int) ; 
 int /*<<< orphan*/  create_virtual_node (struct tree_balance*,int) ; 
 int dc_size (int /*<<< orphan*/ ) ; 
 int get_lfree (struct tree_balance*,int) ; 
 int get_parents (struct tree_balance*,int) ; 
 int get_rfree (struct tree_balance*,int) ; 
 scalar_t__ is_left_neighbor_in_cache (struct tree_balance*,int) ; 
 int /*<<< orphan*/  set_parameters (struct tree_balance*,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int dc_check_balance_internal(struct tree_balance *tb, int h)
{
	struct virtual_node *vn = tb->tb_vn;

	/*
	 * Sh is the node whose balance is currently being checked,
	 * and Fh is its father.
	 */
	struct buffer_head *Sh, *Fh;
	int ret;
	int lfree, rfree /* free space in L and R */ ;

	Sh = PATH_H_PBUFFER(tb->tb_path, h);
	Fh = PATH_H_PPARENT(tb->tb_path, h);

	/*
	 * using tb->insert_size[h], which is negative in this case,
	 * create_virtual_node calculates:
	 * new_nr_item = number of items node would have if operation is
	 * performed without balancing (new_nr_item);
	 */
	create_virtual_node(tb, h);

	if (!Fh) {		/* S[h] is the root. */
		/* no balancing for higher levels needed */
		if (vn->vn_nr_item > 0) {
			set_parameters(tb, h, 0, 0, 1, NULL, -1, -1);
			return NO_BALANCING_NEEDED;
		}
		/*
		 * new_nr_item == 0.
		 * Current root will be deleted resulting in
		 * decrementing the tree height.
		 */
		set_parameters(tb, h, 0, 0, 0, NULL, -1, -1);
		return CARRY_ON;
	}

	if ((ret = get_parents(tb, h)) != CARRY_ON)
		return ret;

	/* get free space of neighbors */
	rfree = get_rfree(tb, h);
	lfree = get_lfree(tb, h);

	/* determine maximal number of items we can fit into neighbors */
	check_left(tb, h, lfree);
	check_right(tb, h, rfree);

	/*
	 * Balance condition for the internal node is valid.
	 * In this case we balance only if it leads to better packing.
	 */
	if (vn->vn_nr_item >= MIN_NR_KEY(Sh)) {
		/*
		 * Here we join S[h] with one of its neighbors,
		 * which is impossible with greater values of new_nr_item.
		 */
		if (vn->vn_nr_item == MIN_NR_KEY(Sh)) {
			/* All contents of S[h] can be moved to L[h]. */
			if (tb->lnum[h] >= vn->vn_nr_item + 1) {
				int n;
				int order_L;

				order_L =
				    ((n =
				      PATH_H_B_ITEM_ORDER(tb->tb_path,
							  h)) ==
				     0) ? B_NR_ITEMS(tb->FL[h]) : n - 1;
				n = dc_size(B_N_CHILD(tb->FL[h], order_L)) /
				    (DC_SIZE + KEY_SIZE);
				set_parameters(tb, h, -n - 1, 0, 0, NULL, -1,
					       -1);
				return CARRY_ON;
			}

			/* All contents of S[h] can be moved to R[h]. */
			if (tb->rnum[h] >= vn->vn_nr_item + 1) {
				int n;
				int order_R;

				order_R =
				    ((n =
				      PATH_H_B_ITEM_ORDER(tb->tb_path,
							  h)) ==
				     B_NR_ITEMS(Fh)) ? 0 : n + 1;
				n = dc_size(B_N_CHILD(tb->FR[h], order_R)) /
				    (DC_SIZE + KEY_SIZE);
				set_parameters(tb, h, 0, -n - 1, 0, NULL, -1,
					       -1);
				return CARRY_ON;
			}
		}

		/*
		 * All contents of S[h] can be moved to the neighbors
		 * (L[h] & R[h]).
		 */
		if (tb->rnum[h] + tb->lnum[h] >= vn->vn_nr_item + 1) {
			int to_r;

			to_r =
			    ((MAX_NR_KEY(Sh) << 1) + 2 - tb->lnum[h] -
			     tb->rnum[h] + vn->vn_nr_item + 1) / 2 -
			    (MAX_NR_KEY(Sh) + 1 - tb->rnum[h]);
			set_parameters(tb, h, vn->vn_nr_item + 1 - to_r, to_r,
				       0, NULL, -1, -1);
			return CARRY_ON;
		}

		/* Balancing does not lead to better packing. */
		set_parameters(tb, h, 0, 0, 1, NULL, -1, -1);
		return NO_BALANCING_NEEDED;
	}

	/*
	 * Current node contain insufficient number of items.
	 * Balancing is required.
	 */
	/* Check whether we can merge S[h] with left neighbor. */
	if (tb->lnum[h] >= vn->vn_nr_item + 1)
		if (is_left_neighbor_in_cache(tb, h)
		    || tb->rnum[h] < vn->vn_nr_item + 1 || !tb->FR[h]) {
			int n;
			int order_L;

			order_L =
			    ((n =
			      PATH_H_B_ITEM_ORDER(tb->tb_path,
						  h)) ==
			     0) ? B_NR_ITEMS(tb->FL[h]) : n - 1;
			n = dc_size(B_N_CHILD(tb->FL[h], order_L)) / (DC_SIZE +
								      KEY_SIZE);
			set_parameters(tb, h, -n - 1, 0, 0, NULL, -1, -1);
			return CARRY_ON;
		}

	/* Check whether we can merge S[h] with right neighbor. */
	if (tb->rnum[h] >= vn->vn_nr_item + 1) {
		int n;
		int order_R;

		order_R =
		    ((n =
		      PATH_H_B_ITEM_ORDER(tb->tb_path,
					  h)) == B_NR_ITEMS(Fh)) ? 0 : (n + 1);
		n = dc_size(B_N_CHILD(tb->FR[h], order_R)) / (DC_SIZE +
							      KEY_SIZE);
		set_parameters(tb, h, 0, -n - 1, 0, NULL, -1, -1);
		return CARRY_ON;
	}

	/* All contents of S[h] can be moved to the neighbors (L[h] & R[h]). */
	if (tb->rnum[h] + tb->lnum[h] >= vn->vn_nr_item + 1) {
		int to_r;

		to_r =
		    ((MAX_NR_KEY(Sh) << 1) + 2 - tb->lnum[h] - tb->rnum[h] +
		     vn->vn_nr_item + 1) / 2 - (MAX_NR_KEY(Sh) + 1 -
						tb->rnum[h]);
		set_parameters(tb, h, vn->vn_nr_item + 1 - to_r, to_r, 0, NULL,
			       -1, -1);
		return CARRY_ON;
	}

	/* For internal nodes try to borrow item from a neighbor */
	RFALSE(!tb->FL[h] && !tb->FR[h], "vs-8235: trying to borrow for root");

	/* Borrow one or two items from caching neighbor */
	if (is_left_neighbor_in_cache(tb, h) || !tb->FR[h]) {
		int from_l;

		from_l =
		    (MAX_NR_KEY(Sh) + 1 - tb->lnum[h] + vn->vn_nr_item +
		     1) / 2 - (vn->vn_nr_item + 1);
		set_parameters(tb, h, -from_l, 0, 1, NULL, -1, -1);
		return CARRY_ON;
	}

	set_parameters(tb, h, 0,
		       -((MAX_NR_KEY(Sh) + 1 - tb->rnum[h] + vn->vn_nr_item +
			  1) / 2 - (vn->vn_nr_item + 1)), 1, NULL, -1, -1);
	return CARRY_ON;
}