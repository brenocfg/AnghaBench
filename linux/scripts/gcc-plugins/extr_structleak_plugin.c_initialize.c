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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  gimple_stmt_iterator ;
typedef  int /*<<< orphan*/  gimple ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
 scalar_t__ CONSTRUCTOR ; 
 int /*<<< orphan*/  DECL_SOURCE_LOCATION (scalar_t__) ; 
 int /*<<< orphan*/  ENTRY_BLOCK_PTR_FOR_FN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GSI_NEW_STMT ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 scalar_t__ TREE_CLOBBER_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_constructor (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ byref ; 
 int /*<<< orphan*/  cfun ; 
 scalar_t__ fold_convert (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_assign_rhs1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimple_assign_single_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimple_build_assign (scalar_t__,scalar_t__) ; 
 scalar_t__ gimple_get_lhs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_after_labels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gsi_start_bb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  single_succ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void initialize(tree var)
{
	basic_block bb;
	gimple_stmt_iterator gsi;
	tree initializer;
	gimple init_stmt;
	tree type;

	/* this is the original entry bb before the forced split */
	bb = single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun));

	/* first check if variable is already initialized, warn otherwise */
	for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
		gimple stmt = gsi_stmt(gsi);
		tree rhs1;

		/* we're looking for an assignment of a single rhs... */
		if (!gimple_assign_single_p(stmt))
			continue;
		rhs1 = gimple_assign_rhs1(stmt);
#if BUILDING_GCC_VERSION >= 4007
		/* ... of a non-clobbering expression... */
		if (TREE_CLOBBER_P(rhs1))
			continue;
#endif
		/* ... to our variable... */
		if (gimple_get_lhs(stmt) != var)
			continue;
		/* if it's an initializer then we're good */
		if (TREE_CODE(rhs1) == CONSTRUCTOR)
			return;
	}

	/* these aren't the 0days you're looking for */
	if (verbose)
		inform(DECL_SOURCE_LOCATION(var),
			"%s variable will be forcibly initialized",
			(byref && TREE_ADDRESSABLE(var)) ? "byref"
							 : "userspace");

	/* build the initializer expression */
	type = TREE_TYPE(var);
	if (AGGREGATE_TYPE_P(type))
		initializer = build_constructor(type, NULL);
	else
		initializer = fold_convert(type, integer_zero_node);

	/* build the initializer stmt */
	init_stmt = gimple_build_assign(var, initializer);
	gsi = gsi_after_labels(single_succ(ENTRY_BLOCK_PTR_FOR_FN(cfun)));
	gsi_insert_before(&gsi, init_stmt, GSI_NEW_STMT);
	update_stmt(init_stmt);
}