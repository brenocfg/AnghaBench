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
struct TYPE_3__ {scalar_t__ missing_ok; int /*<<< orphan*/  relation; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ AlterTableStmt ;

/* Variables and functions */
 int /*<<< orphan*/  RVR_MISSING_OK ; 
 int /*<<< orphan*/  RangeVarCallbackForAlterRelation ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

Oid
AlterTableLookupRelation(AlterTableStmt *stmt, LOCKMODE lockmode)
{
	return RangeVarGetRelidExtended(stmt->relation, lockmode,
									stmt->missing_ok ? RVR_MISSING_OK : 0,
									RangeVarCallbackForAlterRelation,
									(void *) stmt);
}