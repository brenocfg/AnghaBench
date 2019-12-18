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
typedef  int /*<<< orphan*/  IntoClause ;

/* Variables and functions */
 int /*<<< orphan*/  OnCommitAction ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accessMethod ; 
 int /*<<< orphan*/  colNames ; 
 int /*<<< orphan*/  onCommit ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  rel ; 
 int /*<<< orphan*/  skipData ; 
 int /*<<< orphan*/  tableSpaceName ; 
 int /*<<< orphan*/  viewQuery ; 

__attribute__((used)) static void
_outIntoClause(StringInfo str, const IntoClause *node)
{
	WRITE_NODE_TYPE("INTOCLAUSE");

	WRITE_NODE_FIELD(rel);
	WRITE_NODE_FIELD(colNames);
	WRITE_STRING_FIELD(accessMethod);
	WRITE_NODE_FIELD(options);
	WRITE_ENUM_FIELD(onCommit, OnCommitAction);
	WRITE_STRING_FIELD(tableSpaceName);
	WRITE_NODE_FIELD(viewQuery);
	WRITE_BOOL_FIELD(skipData);
}