#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  subtype; } ;
struct TYPE_9__ {TYPE_1__* rd_rel; } ;
struct TYPE_8__ {scalar_t__ relkind; scalar_t__ reloftype; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_3__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  ATTypedTableRecursion (int /*<<< orphan*/ **,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT_DropColumnRecurse ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
ATPrepDropColumn(List **wqueue, Relation rel, bool recurse, bool recursing,
				 AlterTableCmd *cmd, LOCKMODE lockmode)
{
	if (rel->rd_rel->reloftype && !recursing)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot drop column from typed table")));

	if (rel->rd_rel->relkind == RELKIND_COMPOSITE_TYPE)
		ATTypedTableRecursion(wqueue, rel, cmd, lockmode);

	if (recurse)
		cmd->subtype = AT_DropColumnRecurse;
}