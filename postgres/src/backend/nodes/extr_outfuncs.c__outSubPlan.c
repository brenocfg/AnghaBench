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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SubLinkType ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_FLOAT_FIELD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static void
_outSubPlan(StringInfo str, const SubPlan *node)
{
	WRITE_NODE_TYPE("SUBPLAN");

	WRITE_ENUM_FIELD(subLinkType, SubLinkType);
	WRITE_NODE_FIELD(testexpr);
	WRITE_NODE_FIELD(paramIds);
	WRITE_INT_FIELD(plan_id);
	WRITE_STRING_FIELD(plan_name);
	WRITE_OID_FIELD(firstColType);
	WRITE_INT_FIELD(firstColTypmod);
	WRITE_OID_FIELD(firstColCollation);
	WRITE_BOOL_FIELD(useHashTable);
	WRITE_BOOL_FIELD(unknownEqFalse);
	WRITE_BOOL_FIELD(parallel_safe);
	WRITE_NODE_FIELD(setParam);
	WRITE_NODE_FIELD(parParam);
	WRITE_NODE_FIELD(args);
	WRITE_FLOAT_FIELD(startup_cost, "%.2f");
	WRITE_FLOAT_FIELD(per_call_cost, "%.2f");
}