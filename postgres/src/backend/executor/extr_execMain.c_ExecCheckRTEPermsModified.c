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
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  scalar_t__ AttrNumber ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACLMASK_ANY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ InvalidAttrNumber ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ *) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pg_attribute_aclcheck (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_attribute_aclcheck_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ExecCheckRTEPermsModified(Oid relOid, Oid userid, Bitmapset *modifiedCols,
						  AclMode requiredPerms)
{
	int			col = -1;

	/*
	 * When the query doesn't explicitly update any columns, allow the query
	 * if we have permission on any column of the rel.  This is to handle
	 * SELECT FOR UPDATE as well as possible corner cases in UPDATE.
	 */
	if (bms_is_empty(modifiedCols))
	{
		if (pg_attribute_aclcheck_all(relOid, userid, requiredPerms,
									  ACLMASK_ANY) != ACLCHECK_OK)
			return false;
	}

	while ((col = bms_next_member(modifiedCols, col)) >= 0)
	{
		/* bit #s are offset by FirstLowInvalidHeapAttributeNumber */
		AttrNumber	attno = col + FirstLowInvalidHeapAttributeNumber;

		if (attno == InvalidAttrNumber)
		{
			/* whole-row reference can't happen here */
			elog(ERROR, "whole-row update is not implemented");
		}
		else
		{
			if (pg_attribute_aclcheck(relOid, attno, userid,
									  requiredPerms) != ACLCHECK_OK)
				return false;
		}
	}
	return true;
}