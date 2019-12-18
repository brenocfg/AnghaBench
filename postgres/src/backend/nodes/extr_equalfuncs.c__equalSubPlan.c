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
typedef  int /*<<< orphan*/  SubPlan ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  firstColCollation ; 
 int /*<<< orphan*/  firstColType ; 
 int /*<<< orphan*/  firstColTypmod ; 
 int /*<<< orphan*/  parParam ; 
 int /*<<< orphan*/  parallel_safe ; 
 int /*<<< orphan*/  paramIds ; 
 int /*<<< orphan*/  per_call_cost ; 
 int /*<<< orphan*/  plan_id ; 
 int /*<<< orphan*/  plan_name ; 
 int /*<<< orphan*/  setParam ; 
 int /*<<< orphan*/  startup_cost ; 
 int /*<<< orphan*/  subLinkType ; 
 int /*<<< orphan*/  testexpr ; 
 int /*<<< orphan*/  unknownEqFalse ; 
 int /*<<< orphan*/  useHashTable ; 

__attribute__((used)) static bool
_equalSubPlan(const SubPlan *a, const SubPlan *b)
{
	COMPARE_SCALAR_FIELD(subLinkType);
	COMPARE_NODE_FIELD(testexpr);
	COMPARE_NODE_FIELD(paramIds);
	COMPARE_SCALAR_FIELD(plan_id);
	COMPARE_STRING_FIELD(plan_name);
	COMPARE_SCALAR_FIELD(firstColType);
	COMPARE_SCALAR_FIELD(firstColTypmod);
	COMPARE_SCALAR_FIELD(firstColCollation);
	COMPARE_SCALAR_FIELD(useHashTable);
	COMPARE_SCALAR_FIELD(unknownEqFalse);
	COMPARE_SCALAR_FIELD(parallel_safe);
	COMPARE_NODE_FIELD(setParam);
	COMPARE_NODE_FIELD(parParam);
	COMPARE_NODE_FIELD(args);
	COMPARE_SCALAR_FIELD(startup_cost);
	COMPARE_SCALAR_FIELD(per_call_cost);

	return true;
}