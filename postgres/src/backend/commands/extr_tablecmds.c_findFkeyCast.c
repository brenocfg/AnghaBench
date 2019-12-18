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
typedef  scalar_t__ Oid ;
typedef  scalar_t__ CoercionPathType ;

/* Variables and functions */
 int /*<<< orphan*/  COERCION_IMPLICIT ; 
 scalar_t__ COERCION_PATH_NONE ; 
 scalar_t__ COERCION_PATH_RELABELTYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ find_coercion_pathway (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static CoercionPathType
findFkeyCast(Oid targetTypeId, Oid sourceTypeId, Oid *funcid)
{
	CoercionPathType ret;

	if (targetTypeId == sourceTypeId)
	{
		ret = COERCION_PATH_RELABELTYPE;
		*funcid = InvalidOid;
	}
	else
	{
		ret = find_coercion_pathway(targetTypeId, sourceTypeId,
									COERCION_IMPLICIT, funcid);
		if (ret == COERCION_PATH_NONE)
			/* A previously-relied-upon cast is now gone. */
			elog(ERROR, "could not find cast from %u to %u",
				 sourceTypeId, targetTypeId);
	}

	return ret;
}