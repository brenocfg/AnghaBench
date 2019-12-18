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
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  ModifyTablePath ;

/* Variables and functions */
 int /*<<< orphan*/  CmdType ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_UINT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outPathInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  canSetTag ; 
 int /*<<< orphan*/  epqParam ; 
 int /*<<< orphan*/  nominalRelation ; 
 int /*<<< orphan*/  onconflict ; 
 int /*<<< orphan*/  operation ; 
 int /*<<< orphan*/  partColsUpdated ; 
 int /*<<< orphan*/  resultRelations ; 
 int /*<<< orphan*/  returningLists ; 
 int /*<<< orphan*/  rootRelation ; 
 int /*<<< orphan*/  rowMarks ; 
 int /*<<< orphan*/  subpaths ; 
 int /*<<< orphan*/  subroots ; 
 int /*<<< orphan*/  withCheckOptionLists ; 

__attribute__((used)) static void
_outModifyTablePath(StringInfo str, const ModifyTablePath *node)
{
	WRITE_NODE_TYPE("MODIFYTABLEPATH");

	_outPathInfo(str, (const Path *) node);

	WRITE_ENUM_FIELD(operation, CmdType);
	WRITE_BOOL_FIELD(canSetTag);
	WRITE_UINT_FIELD(nominalRelation);
	WRITE_UINT_FIELD(rootRelation);
	WRITE_BOOL_FIELD(partColsUpdated);
	WRITE_NODE_FIELD(resultRelations);
	WRITE_NODE_FIELD(subpaths);
	WRITE_NODE_FIELD(subroots);
	WRITE_NODE_FIELD(withCheckOptionLists);
	WRITE_NODE_FIELD(returningLists);
	WRITE_NODE_FIELD(rowMarks);
	WRITE_NODE_FIELD(onconflict);
	WRITE_INT_FIELD(epqParam);
}