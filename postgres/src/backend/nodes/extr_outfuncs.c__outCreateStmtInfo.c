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
typedef  int /*<<< orphan*/  CreateStmt ;

/* Variables and functions */
 int /*<<< orphan*/  OnCommitAction ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accessMethod ; 
 int /*<<< orphan*/  constraints ; 
 int /*<<< orphan*/  if_not_exists ; 
 int /*<<< orphan*/  inhRelations ; 
 int /*<<< orphan*/  ofTypename ; 
 int /*<<< orphan*/  oncommit ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  partbound ; 
 int /*<<< orphan*/  partspec ; 
 int /*<<< orphan*/  relation ; 
 int /*<<< orphan*/  tableElts ; 
 int /*<<< orphan*/  tablespacename ; 

__attribute__((used)) static void
_outCreateStmtInfo(StringInfo str, const CreateStmt *node)
{
	WRITE_NODE_FIELD(relation);
	WRITE_NODE_FIELD(tableElts);
	WRITE_NODE_FIELD(inhRelations);
	WRITE_NODE_FIELD(partspec);
	WRITE_NODE_FIELD(partbound);
	WRITE_NODE_FIELD(ofTypename);
	WRITE_NODE_FIELD(constraints);
	WRITE_NODE_FIELD(options);
	WRITE_ENUM_FIELD(oncommit, OnCommitAction);
	WRITE_STRING_FIELD(tablespacename);
	WRITE_STRING_FIELD(accessMethod);
	WRITE_BOOL_FIELD(if_not_exists);
}