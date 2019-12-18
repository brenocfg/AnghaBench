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
struct TYPE_3__ {scalar_t__ rtekind; int requiredPerms; int /*<<< orphan*/  updatedCols; int /*<<< orphan*/  insertedCols; int /*<<< orphan*/  selectedCols; scalar_t__ checkAsUser; scalar_t__ relid; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  scalar_t__ Oid ;
typedef  scalar_t__ AttrNumber ;
typedef  int AclMode ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACLMASK_ALL ; 
 int /*<<< orphan*/  ACLMASK_ANY ; 
 int ACL_INSERT ; 
 int ACL_SELECT ; 
 int ACL_UPDATE ; 
 int /*<<< orphan*/  ExecCheckRTEPermsModified (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 scalar_t__ GetUserId () ; 
 scalar_t__ InvalidAttrNumber ; 
 scalar_t__ RTE_RELATION ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pg_attribute_aclcheck (scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ pg_attribute_aclcheck_all (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int pg_class_aclmask (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ExecCheckRTEPerms(RangeTblEntry *rte)
{
	AclMode		requiredPerms;
	AclMode		relPerms;
	AclMode		remainingPerms;
	Oid			relOid;
	Oid			userid;

	/*
	 * Only plain-relation RTEs need to be checked here.  Function RTEs are
	 * checked when the function is prepared for execution.  Join, subquery,
	 * and special RTEs need no checks.
	 */
	if (rte->rtekind != RTE_RELATION)
		return true;

	/*
	 * No work if requiredPerms is empty.
	 */
	requiredPerms = rte->requiredPerms;
	if (requiredPerms == 0)
		return true;

	relOid = rte->relid;

	/*
	 * userid to check as: current user unless we have a setuid indication.
	 *
	 * Note: GetUserId() is presently fast enough that there's no harm in
	 * calling it separately for each RTE.  If that stops being true, we could
	 * call it once in ExecCheckRTPerms and pass the userid down from there.
	 * But for now, no need for the extra clutter.
	 */
	userid = rte->checkAsUser ? rte->checkAsUser : GetUserId();

	/*
	 * We must have *all* the requiredPerms bits, but some of the bits can be
	 * satisfied from column-level rather than relation-level permissions.
	 * First, remove any bits that are satisfied by relation permissions.
	 */
	relPerms = pg_class_aclmask(relOid, userid, requiredPerms, ACLMASK_ALL);
	remainingPerms = requiredPerms & ~relPerms;
	if (remainingPerms != 0)
	{
		int			col = -1;

		/*
		 * If we lack any permissions that exist only as relation permissions,
		 * we can fail straight away.
		 */
		if (remainingPerms & ~(ACL_SELECT | ACL_INSERT | ACL_UPDATE))
			return false;

		/*
		 * Check to see if we have the needed privileges at column level.
		 *
		 * Note: failures just report a table-level error; it would be nicer
		 * to report a column-level error if we have some but not all of the
		 * column privileges.
		 */
		if (remainingPerms & ACL_SELECT)
		{
			/*
			 * When the query doesn't explicitly reference any columns (for
			 * example, SELECT COUNT(*) FROM table), allow the query if we
			 * have SELECT on any column of the rel, as per SQL spec.
			 */
			if (bms_is_empty(rte->selectedCols))
			{
				if (pg_attribute_aclcheck_all(relOid, userid, ACL_SELECT,
											  ACLMASK_ANY) != ACLCHECK_OK)
					return false;
			}

			while ((col = bms_next_member(rte->selectedCols, col)) >= 0)
			{
				/* bit #s are offset by FirstLowInvalidHeapAttributeNumber */
				AttrNumber	attno = col + FirstLowInvalidHeapAttributeNumber;

				if (attno == InvalidAttrNumber)
				{
					/* Whole-row reference, must have priv on all cols */
					if (pg_attribute_aclcheck_all(relOid, userid, ACL_SELECT,
												  ACLMASK_ALL) != ACLCHECK_OK)
						return false;
				}
				else
				{
					if (pg_attribute_aclcheck(relOid, attno, userid,
											  ACL_SELECT) != ACLCHECK_OK)
						return false;
				}
			}
		}

		/*
		 * Basically the same for the mod columns, for both INSERT and UPDATE
		 * privilege as specified by remainingPerms.
		 */
		if (remainingPerms & ACL_INSERT && !ExecCheckRTEPermsModified(relOid,
																	  userid,
																	  rte->insertedCols,
																	  ACL_INSERT))
			return false;

		if (remainingPerms & ACL_UPDATE && !ExecCheckRTEPermsModified(relOid,
																	  userid,
																	  rte->updatedCols,
																	  ACL_UPDATE))
			return false;
	}
	return true;
}