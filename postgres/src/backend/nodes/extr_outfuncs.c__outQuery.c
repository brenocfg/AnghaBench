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
struct TYPE_3__ {scalar_t__ utilityStmt; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ Query ;

/* Variables and functions */
 int /*<<< orphan*/  CmdType ; 
 int /*<<< orphan*/  OverridingKind ; 
 int /*<<< orphan*/  QuerySource ; 
#define  T_CreateStmt 131 
#define  T_DeclareCursorStmt 130 
#define  T_IndexStmt 129 
#define  T_NotifyStmt 128 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_LOCATION_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  canSetTag ; 
 int /*<<< orphan*/  commandType ; 
 int /*<<< orphan*/  constraintDeps ; 
 int /*<<< orphan*/  cteList ; 
 int /*<<< orphan*/  distinctClause ; 
 int /*<<< orphan*/  groupClause ; 
 int /*<<< orphan*/  groupingSets ; 
 int /*<<< orphan*/  hasAggs ; 
 int /*<<< orphan*/  hasDistinctOn ; 
 int /*<<< orphan*/  hasForUpdate ; 
 int /*<<< orphan*/  hasModifyingCTE ; 
 int /*<<< orphan*/  hasRecursive ; 
 int /*<<< orphan*/  hasRowSecurity ; 
 int /*<<< orphan*/  hasSubLinks ; 
 int /*<<< orphan*/  hasTargetSRFs ; 
 int /*<<< orphan*/  hasWindowFuncs ; 
 int /*<<< orphan*/  havingQual ; 
 int /*<<< orphan*/  jointree ; 
 int /*<<< orphan*/  limitCount ; 
 int /*<<< orphan*/  limitOffset ; 
 int nodeTag (scalar_t__) ; 
 int /*<<< orphan*/  onConflict ; 
 int /*<<< orphan*/  override ; 
 int /*<<< orphan*/  querySource ; 
 int /*<<< orphan*/  resultRelation ; 
 int /*<<< orphan*/  returningList ; 
 int /*<<< orphan*/  rowMarks ; 
 int /*<<< orphan*/  rtable ; 
 int /*<<< orphan*/  setOperations ; 
 int /*<<< orphan*/  sortClause ; 
 int /*<<< orphan*/  stmt_len ; 
 int /*<<< orphan*/  stmt_location ; 
 int /*<<< orphan*/  targetList ; 
 int /*<<< orphan*/  utilityStmt ; 
 int /*<<< orphan*/  windowClause ; 
 int /*<<< orphan*/  withCheckOptions ; 

__attribute__((used)) static void
_outQuery(StringInfo str, const Query *node)
{
	WRITE_NODE_TYPE("QUERY");

	WRITE_ENUM_FIELD(commandType, CmdType);
	WRITE_ENUM_FIELD(querySource, QuerySource);
	/* we intentionally do not print the queryId field */
	WRITE_BOOL_FIELD(canSetTag);

	/*
	 * Hack to work around missing outfuncs routines for a lot of the
	 * utility-statement node types.  (The only one we actually *need* for
	 * rules support is NotifyStmt.)  Someday we ought to support 'em all, but
	 * for the meantime do this to avoid getting lots of warnings when running
	 * with debug_print_parse on.
	 */
	if (node->utilityStmt)
	{
		switch (nodeTag(node->utilityStmt))
		{
			case T_CreateStmt:
			case T_IndexStmt:
			case T_NotifyStmt:
			case T_DeclareCursorStmt:
				WRITE_NODE_FIELD(utilityStmt);
				break;
			default:
				appendStringInfoString(str, " :utilityStmt ?");
				break;
		}
	}
	else
		appendStringInfoString(str, " :utilityStmt <>");

	WRITE_INT_FIELD(resultRelation);
	WRITE_BOOL_FIELD(hasAggs);
	WRITE_BOOL_FIELD(hasWindowFuncs);
	WRITE_BOOL_FIELD(hasTargetSRFs);
	WRITE_BOOL_FIELD(hasSubLinks);
	WRITE_BOOL_FIELD(hasDistinctOn);
	WRITE_BOOL_FIELD(hasRecursive);
	WRITE_BOOL_FIELD(hasModifyingCTE);
	WRITE_BOOL_FIELD(hasForUpdate);
	WRITE_BOOL_FIELD(hasRowSecurity);
	WRITE_NODE_FIELD(cteList);
	WRITE_NODE_FIELD(rtable);
	WRITE_NODE_FIELD(jointree);
	WRITE_NODE_FIELD(targetList);
	WRITE_ENUM_FIELD(override, OverridingKind);
	WRITE_NODE_FIELD(onConflict);
	WRITE_NODE_FIELD(returningList);
	WRITE_NODE_FIELD(groupClause);
	WRITE_NODE_FIELD(groupingSets);
	WRITE_NODE_FIELD(havingQual);
	WRITE_NODE_FIELD(windowClause);
	WRITE_NODE_FIELD(distinctClause);
	WRITE_NODE_FIELD(sortClause);
	WRITE_NODE_FIELD(limitOffset);
	WRITE_NODE_FIELD(limitCount);
	WRITE_NODE_FIELD(rowMarks);
	WRITE_NODE_FIELD(setOperations);
	WRITE_NODE_FIELD(constraintDeps);
	WRITE_NODE_FIELD(withCheckOptions);
	WRITE_LOCATION_FIELD(stmt_location);
	WRITE_LOCATION_FIELD(stmt_len);
}