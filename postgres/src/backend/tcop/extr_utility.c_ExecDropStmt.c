#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int removeType; int /*<<< orphan*/  concurrent; } ;
typedef  TYPE_1__ DropStmt ;

/* Variables and functions */
#define  OBJECT_FOREIGN_TABLE 133 
#define  OBJECT_INDEX 132 
#define  OBJECT_MATVIEW 131 
#define  OBJECT_SEQUENCE 130 
#define  OBJECT_TABLE 129 
#define  OBJECT_VIEW 128 
 int /*<<< orphan*/  PreventInTransactionBlock (int,char*) ; 
 int /*<<< orphan*/  RemoveObjects (TYPE_1__*) ; 
 int /*<<< orphan*/  RemoveRelations (TYPE_1__*) ; 

__attribute__((used)) static void
ExecDropStmt(DropStmt *stmt, bool isTopLevel)
{
	switch (stmt->removeType)
	{
		case OBJECT_INDEX:
			if (stmt->concurrent)
				PreventInTransactionBlock(isTopLevel,
										  "DROP INDEX CONCURRENTLY");
			/* fall through */

		case OBJECT_TABLE:
		case OBJECT_SEQUENCE:
		case OBJECT_VIEW:
		case OBJECT_MATVIEW:
		case OBJECT_FOREIGN_TABLE:
			RemoveRelations(stmt);
			break;
		default:
			RemoveObjects(stmt);
			break;
	}
}