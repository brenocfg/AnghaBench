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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OAT_FUNCTION_EXECUTE ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  object_access_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
RunFunctionExecuteHook(Oid objectId)
{
	/* caller should check, but just in case... */
	Assert(object_access_hook != NULL);

	(*object_access_hook) (OAT_FUNCTION_EXECUTE,
						   ProcedureRelationId, objectId, 0,
						   NULL);
}