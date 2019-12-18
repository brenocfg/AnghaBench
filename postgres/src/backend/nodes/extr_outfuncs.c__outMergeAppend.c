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
typedef  TYPE_1__ MergeAppend ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ATTRNUMBER_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  collations ; 
 int /*<<< orphan*/  mergeplans ; 
 int /*<<< orphan*/  nullsFirst ; 
 int /*<<< orphan*/  numCols ; 
 int /*<<< orphan*/  part_prune_info ; 
 int /*<<< orphan*/  sortColIdx ; 
 int /*<<< orphan*/  sortOperators ; 

__attribute__((used)) static void
_outMergeAppend(StringInfo str, const MergeAppend *node)
{
	WRITE_NODE_TYPE("MERGEAPPEND");

	_outPlanInfo(str, (const Plan *) node);

	WRITE_NODE_FIELD(mergeplans);
	WRITE_INT_FIELD(numCols);
	WRITE_ATTRNUMBER_ARRAY(sortColIdx, node->numCols);
	WRITE_OID_ARRAY(sortOperators, node->numCols);
	WRITE_OID_ARRAY(collations, node->numCols);
	WRITE_BOOL_ARRAY(nullsFirst, node->numCols);
	WRITE_NODE_FIELD(part_prune_info);
}