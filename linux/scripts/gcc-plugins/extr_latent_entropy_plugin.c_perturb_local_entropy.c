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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  gimple_stmt_iterator ;
typedef  int /*<<< orphan*/  gimple ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  GSI_NEW_STMT ; 
 int /*<<< orphan*/  create_assign (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_op (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gsi_after_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perturb_local_entropy(basic_block bb, tree local_entropy)
{
	gimple_stmt_iterator gsi;
	gimple assign;
	tree rhs;
	enum tree_code op;

	op = get_op(&rhs);
	assign = create_assign(op, local_entropy, local_entropy, rhs);
	gsi = gsi_after_labels(bb);
	gsi_insert_before(&gsi, assign, GSI_NEW_STMT);
	update_stmt(assign);
}