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
typedef  int /*<<< orphan*/  CreateForeignTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _outCreateStmtInfo (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  servername ; 

__attribute__((used)) static void
_outCreateForeignTableStmt(StringInfo str, const CreateForeignTableStmt *node)
{
	WRITE_NODE_TYPE("CREATEFOREIGNTABLESTMT");

	_outCreateStmtInfo(str, (const CreateStmt *) node);

	WRITE_STRING_FIELD(servername);
	WRITE_NODE_FIELD(options);
}