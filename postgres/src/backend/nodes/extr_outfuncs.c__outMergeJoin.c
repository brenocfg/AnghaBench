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
struct TYPE_3__ {int /*<<< orphan*/  mergeclauses; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ MergeJoin ;
typedef  int /*<<< orphan*/  Join ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BOOL_ARRAY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_ARRAY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _outJoinPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mergeCollations ; 
 int /*<<< orphan*/  mergeFamilies ; 
 int /*<<< orphan*/  mergeNullsFirst ; 
 int /*<<< orphan*/  mergeStrategies ; 
 int /*<<< orphan*/  mergeclauses ; 
 int /*<<< orphan*/  skip_mark_restore ; 

__attribute__((used)) static void
_outMergeJoin(StringInfo str, const MergeJoin *node)
{
	int			numCols;

	WRITE_NODE_TYPE("MERGEJOIN");

	_outJoinPlanInfo(str, (const Join *) node);

	WRITE_BOOL_FIELD(skip_mark_restore);
	WRITE_NODE_FIELD(mergeclauses);

	numCols = list_length(node->mergeclauses);

	WRITE_OID_ARRAY(mergeFamilies, numCols);
	WRITE_OID_ARRAY(mergeCollations, numCols);
	WRITE_INT_ARRAY(mergeStrategies, numCols);
	WRITE_BOOL_ARRAY(mergeNullsFirst, numCols);
}