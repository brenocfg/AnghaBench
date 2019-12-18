#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  numCols; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ SetOp ;
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
 int /*<<< orphan*/  SetOpCmd ; 
 int /*<<< orphan*/  SetOpStrategy ; 
 int /*<<< orphan*/  WRITE_ATTRNUMBER_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LONG_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cmd ; 
 int /*<<< orphan*/  dupColIdx ; 
 int /*<<< orphan*/  dupCollations ; 
 int /*<<< orphan*/  dupOperators ; 
 int /*<<< orphan*/  firstFlag ; 
 int /*<<< orphan*/  flagColIdx ; 
 int /*<<< orphan*/  numCols ; 
 int /*<<< orphan*/  numGroups ; 
 int /*<<< orphan*/  strategy ; 

__attribute__((used)) static void
_outSetOp(StringInfo str, const SetOp *node)
{
	WRITE_NODE_TYPE("SETOP");

	_outPlanInfo(str, (const Plan *) node);

	WRITE_ENUM_FIELD(cmd, SetOpCmd);
	WRITE_ENUM_FIELD(strategy, SetOpStrategy);
	WRITE_INT_FIELD(numCols);
	WRITE_ATTRNUMBER_ARRAY(dupColIdx, node->numCols);
	WRITE_OID_ARRAY(dupOperators, node->numCols);
	WRITE_OID_ARRAY(dupCollations, node->numCols);
	WRITE_INT_FIELD(flagColIdx);
	WRITE_INT_FIELD(firstFlag);
	WRITE_LONG_FIELD(numGroups);
}