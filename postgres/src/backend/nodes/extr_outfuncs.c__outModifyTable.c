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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Plan ;
typedef  int /*<<< orphan*/  ModifyTable ;

/* Variables and functions */
 int /*<<< orphan*/  CmdType ; 
 int /*<<< orphan*/  OnConflictAction ; 
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPlanInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  arbiterIndexes ; 
 int /*<<< orphan*/  canSetTag ; 
 int /*<<< orphan*/  epqParam ; 
 int /*<<< orphan*/  exclRelRTI ; 
 int /*<<< orphan*/  exclRelTlist ; 
 int /*<<< orphan*/  fdwDirectModifyPlans ; 
 int /*<<< orphan*/  fdwPrivLists ; 
 int /*<<< orphan*/  nominalRelation ; 
 int /*<<< orphan*/  onConflictAction ; 
 int /*<<< orphan*/  onConflictSet ; 
 int /*<<< orphan*/  onConflictWhere ; 
 int /*<<< orphan*/  operation ; 
 int /*<<< orphan*/  partColsUpdated ; 
 int /*<<< orphan*/  plans ; 
 int /*<<< orphan*/  resultRelIndex ; 
 int /*<<< orphan*/  resultRelations ; 
 int /*<<< orphan*/  returningLists ; 
 int /*<<< orphan*/  rootRelation ; 
 int /*<<< orphan*/  rootResultRelIndex ; 
 int /*<<< orphan*/  rowMarks ; 
 int /*<<< orphan*/  withCheckOptionLists ; 

__attribute__((used)) static void
_outModifyTable(StringInfo str, const ModifyTable *node)
{
	WRITE_NODE_TYPE("MODIFYTABLE");

	_outPlanInfo(str, (const Plan *) node);

	WRITE_ENUM_FIELD(operation, CmdType);
	WRITE_BOOL_FIELD(canSetTag);
	WRITE_UINT_FIELD(nominalRelation);
	WRITE_UINT_FIELD(rootRelation);
	WRITE_BOOL_FIELD(partColsUpdated);
	WRITE_NODE_FIELD(resultRelations);
	WRITE_INT_FIELD(resultRelIndex);
	WRITE_INT_FIELD(rootResultRelIndex);
	WRITE_NODE_FIELD(plans);
	WRITE_NODE_FIELD(withCheckOptionLists);
	WRITE_NODE_FIELD(returningLists);
	WRITE_NODE_FIELD(fdwPrivLists);
	WRITE_BITMAPSET_FIELD(fdwDirectModifyPlans);
	WRITE_NODE_FIELD(rowMarks);
	WRITE_INT_FIELD(epqParam);
	WRITE_ENUM_FIELD(onConflictAction, OnConflictAction);
	WRITE_NODE_FIELD(arbiterIndexes);
	WRITE_NODE_FIELD(onConflictSet);
	WRITE_NODE_FIELD(onConflictWhere);
	WRITE_UINT_FIELD(exclRelRTI);
	WRITE_NODE_FIELD(exclRelTlist);
}