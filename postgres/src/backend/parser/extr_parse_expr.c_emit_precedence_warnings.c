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
typedef  int /*<<< orphan*/  ParseState ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int PREC_GROUP_IN ; 
 int PREC_GROUP_NOT_IN ; 
 int PREC_GROUP_POSTFIX_IS ; 
 int PREC_GROUP_POSTFIX_OP ; 
 int PREC_GROUP_PREFIX_OP ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 
 scalar_t__* oldprecedence_l ; 
 scalar_t__* oldprecedence_r ; 
 int operator_precedence_group (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
emit_precedence_warnings(ParseState *pstate,
						 int opgroup, const char *opname,
						 Node *lchild, Node *rchild,
						 int location)
{
	int			cgroup;
	const char *copname;

	Assert(opgroup > 0);

	/*
	 * Complain if left child, which should be same or higher precedence
	 * according to current rules, used to be lower precedence.
	 *
	 * Exception to precedence rules: if left child is IN or NOT IN or a
	 * postfix operator, the grouping is syntactically forced regardless of
	 * precedence.
	 */
	cgroup = operator_precedence_group(lchild, &copname);
	if (cgroup > 0)
	{
		if (oldprecedence_l[cgroup] < oldprecedence_r[opgroup] &&
			cgroup != PREC_GROUP_IN &&
			cgroup != PREC_GROUP_NOT_IN &&
			cgroup != PREC_GROUP_POSTFIX_OP &&
			cgroup != PREC_GROUP_POSTFIX_IS)
			ereport(WARNING,
					(errmsg("operator precedence change: %s is now lower precedence than %s",
							opname, copname),
					 parser_errposition(pstate, location)));
	}

	/*
	 * Complain if right child, which should be higher precedence according to
	 * current rules, used to be same or lower precedence.
	 *
	 * Exception to precedence rules: if right child is a prefix operator, the
	 * grouping is syntactically forced regardless of precedence.
	 */
	cgroup = operator_precedence_group(rchild, &copname);
	if (cgroup > 0)
	{
		if (oldprecedence_r[cgroup] <= oldprecedence_l[opgroup] &&
			cgroup != PREC_GROUP_PREFIX_OP)
			ereport(WARNING,
					(errmsg("operator precedence change: %s is now lower precedence than %s",
							opname, copname),
					 parser_errposition(pstate, location)));
	}
}