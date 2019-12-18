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
typedef  int /*<<< orphan*/  RuleStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  actions ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  instead ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  replace ; 
 int /*<<< orphan*/  rulename ; 
 int /*<<< orphan*/  whereClause ; 

__attribute__((used)) static bool
_equalRuleStmt(const RuleStmt *a, const RuleStmt *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_STRING_FIELD(rulename);
	COMPARE_NODE_FIELD(whereClause);
	COMPARE_SCALAR_FIELD(event);
	COMPARE_SCALAR_FIELD(instead);
	COMPARE_NODE_FIELD(actions);
	COMPARE_SCALAR_FIELD(replace);

	return true;
}