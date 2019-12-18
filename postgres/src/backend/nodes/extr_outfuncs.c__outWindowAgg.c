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
struct TYPE_3__ {int /*<<< orphan*/  ordNumCols; int /*<<< orphan*/  partNumCols; } ;
typedef  TYPE_1__ WindowAgg ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Plan ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ATTRNUMBER_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  endInRangeFunc ; 
 int /*<<< orphan*/  endOffset ; 
 int /*<<< orphan*/  frameOptions ; 
 int /*<<< orphan*/  inRangeAsc ; 
 int /*<<< orphan*/  inRangeColl ; 
 int /*<<< orphan*/  inRangeNullsFirst ; 
 int /*<<< orphan*/  ordColIdx ; 
 int /*<<< orphan*/  ordCollations ; 
 int /*<<< orphan*/  ordNumCols ; 
 int /*<<< orphan*/  ordOperators ; 
 int /*<<< orphan*/  partColIdx ; 
 int /*<<< orphan*/  partCollations ; 
 int /*<<< orphan*/  partNumCols ; 
 int /*<<< orphan*/  partOperators ; 
 int /*<<< orphan*/  startInRangeFunc ; 
 int /*<<< orphan*/  startOffset ; 
 int /*<<< orphan*/  winref ; 

__attribute__((used)) static void
_outWindowAgg(StringInfo str, const WindowAgg *node)
{
	WRITE_NODE_TYPE("WINDOWAGG");

	_outPlanInfo(str, (const Plan *) node);

	WRITE_UINT_FIELD(winref);
	WRITE_INT_FIELD(partNumCols);
	WRITE_ATTRNUMBER_ARRAY(partColIdx, node->partNumCols);
	WRITE_OID_ARRAY(partOperators, node->partNumCols);
	WRITE_OID_ARRAY(partCollations, node->partNumCols);
	WRITE_INT_FIELD(ordNumCols);
	WRITE_ATTRNUMBER_ARRAY(ordColIdx, node->ordNumCols);
	WRITE_OID_ARRAY(ordOperators, node->ordNumCols);
	WRITE_OID_ARRAY(ordCollations, node->ordNumCols);
	WRITE_INT_FIELD(frameOptions);
	WRITE_NODE_FIELD(startOffset);
	WRITE_NODE_FIELD(endOffset);
	WRITE_OID_FIELD(startInRangeFunc);
	WRITE_OID_FIELD(endInRangeFunc);
	WRITE_OID_FIELD(inRangeColl);
	WRITE_BOOL_FIELD(inRangeAsc);
	WRITE_BOOL_FIELD(inRangeNullsFirst);
}