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
struct tree_balance {int /*<<< orphan*/ * R; int /*<<< orphan*/ * rkey; int /*<<< orphan*/ * CFR; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEAF_FROM_S_TO_R ; 
 int leaf_move_items (int /*<<< orphan*/ ,struct tree_balance*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int leaf_shift_right(struct tree_balance *tb, int shift_num, int shift_bytes)
{
	int ret_value;

	/*
	 * move shift_num (and shift_bytes) items from S[0] to
	 * right neighbor R[0]
	 */
	ret_value =
	    leaf_move_items(LEAF_FROM_S_TO_R, tb, shift_num, shift_bytes, NULL);

	/* replace rkey in CFR[0] by the 0-th key from R[0] */
	if (shift_num) {
		replace_key(tb, tb->CFR[0], tb->rkey[0], tb->R[0], 0);

	}

	return ret_value;
}