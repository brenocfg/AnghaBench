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
typedef  int /*<<< orphan*/  Plan ;
typedef  TYPE_1__ Group ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ATTRNUMBER_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  grpColIdx ; 
 int /*<<< orphan*/  grpCollations ; 
 int /*<<< orphan*/  grpOperators ; 
 int /*<<< orphan*/  numCols ; 

__attribute__((used)) static void
_outGroup(StringInfo str, const Group *node)
{
	WRITE_NODE_TYPE("GROUP");

	_outPlanInfo(str, (const Plan *) node);

	WRITE_INT_FIELD(numCols);
	WRITE_ATTRNUMBER_ARRAY(grpColIdx, node->numCols);
	WRITE_OID_ARRAY(grpOperators, node->numCols);
	WRITE_OID_ARRAY(grpCollations, node->numCols);
}