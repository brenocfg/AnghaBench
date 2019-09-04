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
struct virtual_node {int vn_nr_item; int /*<<< orphan*/ * vn_vi; } ;
struct tree_balance {int* lnum; int lbytes; int* rnum; int rbytes; struct virtual_node* tb_vn; } ;

/* Variables and functions */
 int op_unit_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_parameters (struct tree_balance*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int is_leaf_removable(struct tree_balance *tb)
{
	struct virtual_node *vn = tb->tb_vn;
	int to_left, to_right;
	int size;
	int remain_items;

	/*
	 * number of items that will be shifted to left (right) neighbor
	 * entirely
	 */
	to_left = tb->lnum[0] - ((tb->lbytes != -1) ? 1 : 0);
	to_right = tb->rnum[0] - ((tb->rbytes != -1) ? 1 : 0);
	remain_items = vn->vn_nr_item;

	/* how many items remain in S[0] after shiftings to neighbors */
	remain_items -= (to_left + to_right);

	/* all content of node can be shifted to neighbors */
	if (remain_items < 1) {
		set_parameters(tb, 0, to_left, vn->vn_nr_item - to_left, 0,
			       NULL, -1, -1);
		return 1;
	}

	/* S[0] is not removable */
	if (remain_items > 1 || tb->lbytes == -1 || tb->rbytes == -1)
		return 0;

	/* check whether we can divide 1 remaining item between neighbors */

	/* get size of remaining item (in item units) */
	size = op_unit_num(&vn->vn_vi[to_left]);

	if (tb->lbytes + tb->rbytes >= size) {
		set_parameters(tb, 0, to_left + 1, to_right + 1, 0, NULL,
			       tb->lbytes, -1);
		return 1;
	}

	return 0;
}