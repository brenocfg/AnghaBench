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
typedef  int /*<<< orphan*/  TableSampleClause ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_OID_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  repeatable ; 
 int /*<<< orphan*/  tsmhandler ; 

__attribute__((used)) static void
_outTableSampleClause(StringInfo str, const TableSampleClause *node)
{
	WRITE_NODE_TYPE("TABLESAMPLECLAUSE");

	WRITE_OID_FIELD(tsmhandler);
	WRITE_NODE_FIELD(args);
	WRITE_NODE_FIELD(repeatable);
}