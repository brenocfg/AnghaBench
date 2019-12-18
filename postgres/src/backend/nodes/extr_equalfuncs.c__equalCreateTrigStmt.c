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
typedef  int /*<<< orphan*/  CreateTrigStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  columns ; 
 int /*<<< orphan*/  constrrel ; 
 int /*<<< orphan*/  deferrable ; 
 int /*<<< orphan*/  events ; 
 int /*<<< orphan*/  funcname ; 
 int /*<<< orphan*/  initdeferred ; 
 int /*<<< orphan*/  isconstraint ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  row ; 
 int /*<<< orphan*/  timing ; 
 int /*<<< orphan*/  transitionRels ; 
 int /*<<< orphan*/  trigname ; 
 int /*<<< orphan*/  whenClause ; 

__attribute__((used)) static bool
_equalCreateTrigStmt(const CreateTrigStmt *a, const CreateTrigStmt *b)
{
	COMPARE_STRING_FIELD(trigname);
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(funcname);
	COMPARE_NODE_FIELD(args);
	COMPARE_SCALAR_FIELD(row);
	COMPARE_SCALAR_FIELD(timing);
	COMPARE_SCALAR_FIELD(events);
	COMPARE_NODE_FIELD(columns);
	COMPARE_NODE_FIELD(whenClause);
	COMPARE_SCALAR_FIELD(isconstraint);
	COMPARE_NODE_FIELD(transitionRels);
	COMPARE_SCALAR_FIELD(deferrable);
	COMPARE_SCALAR_FIELD(initdeferred);
	COMPARE_NODE_FIELD(constrrel);

	return true;
}