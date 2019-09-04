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
typedef  int /*<<< orphan*/  gimple ;
typedef  scalar_t__ const_tree ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  DECL_NAME_POINTER (scalar_t__) ; 
 scalar_t__ GIMPLE_CALL ; 
 scalar_t__ GIMPLE_COND ; 
 scalar_t__ NE_EXPR ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  get_immediate_dominator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_call_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_call_fndecl (int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_code (int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_cond_code (int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_cond_lhs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimple_cond_rhs (int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_get_lhs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool dominated_by_is_err(const_tree rhs, basic_block bb)
{
	basic_block dom;
	gimple dom_stmt;
	gimple call_stmt;
	const_tree dom_lhs;
	const_tree poss_is_err_cond;
	const_tree poss_is_err_func;
	const_tree is_err_arg;

	dom = get_immediate_dominator(CDI_DOMINATORS, bb);
	if (!dom)
		return false;

	dom_stmt = last_stmt(dom);
	if (!dom_stmt)
		return false;

	if (gimple_code(dom_stmt) != GIMPLE_COND)
		return false;

	if (gimple_cond_code(dom_stmt) != NE_EXPR)
		return false;

	if (!integer_zerop(gimple_cond_rhs(dom_stmt)))
		return false;

	poss_is_err_cond = gimple_cond_lhs(dom_stmt);

	if (TREE_CODE(poss_is_err_cond) != SSA_NAME)
		return false;

	call_stmt = SSA_NAME_DEF_STMT(poss_is_err_cond);

	if (gimple_code(call_stmt) != GIMPLE_CALL)
		return false;

	dom_lhs = gimple_get_lhs(call_stmt);
	poss_is_err_func = gimple_call_fndecl(call_stmt);
	if (!poss_is_err_func)
		return false;
	if (dom_lhs != poss_is_err_cond)
		return false;
	if (strcmp(DECL_NAME_POINTER(poss_is_err_func), "IS_ERR"))
		return false;

	is_err_arg = gimple_call_arg(call_stmt, 0);
	if (!is_err_arg)
		return false;

	if (is_err_arg != rhs)
		return false;

	return true;
}