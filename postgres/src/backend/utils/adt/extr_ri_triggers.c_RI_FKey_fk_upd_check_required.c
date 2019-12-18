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
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  Trigger ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {int confmatchtype; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RI_ConstraintInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetTransactionId (int /*<<< orphan*/ ) ; 
#define  FKCONSTR_MATCH_FULL 130 
#define  FKCONSTR_MATCH_PARTIAL 129 
#define  FKCONSTR_MATCH_SIMPLE 128 
 int /*<<< orphan*/  MinTransactionIdAttributeNumber ; 
 int RI_KEYS_ALL_NULL ; 
 int RI_KEYS_SOME_NULL ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 TYPE_1__* ri_FetchConstraintInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ri_KeysEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int ri_NullCheck (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  slot_getsysattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

bool
RI_FKey_fk_upd_check_required(Trigger *trigger, Relation fk_rel,
							  TupleTableSlot *oldslot, TupleTableSlot *newslot)
{
	const RI_ConstraintInfo *riinfo;
	int			ri_nullcheck;
	Datum		xminDatum;
	TransactionId xmin;
	bool		isnull;

	riinfo = ri_FetchConstraintInfo(trigger, fk_rel, false);

	ri_nullcheck = ri_NullCheck(RelationGetDescr(fk_rel), newslot, riinfo, false);

	/*
	 * If all new key values are NULL, the row satisfies the constraint, so no
	 * check is needed.
	 */
	if (ri_nullcheck == RI_KEYS_ALL_NULL)
		return false;

	/*
	 * If some new key values are NULL, the behavior depends on the match
	 * type.
	 */
	else if (ri_nullcheck == RI_KEYS_SOME_NULL)
	{
		switch (riinfo->confmatchtype)
		{
			case FKCONSTR_MATCH_SIMPLE:

				/*
				 * If any new key value is NULL, the row must satisfy the
				 * constraint, so no check is needed.
				 */
				return false;

			case FKCONSTR_MATCH_PARTIAL:

				/*
				 * Don't know, must run full check.
				 */
				break;

			case FKCONSTR_MATCH_FULL:

				/*
				 * If some new key values are NULL, the row fails the
				 * constraint.  We must not throw error here, because the row
				 * might get invalidated before the constraint is to be
				 * checked, but we should queue the event to apply the check
				 * later.
				 */
				return true;
		}
	}

	/*
	 * Continues here for no new key values are NULL, or we couldn't decide
	 * yet.
	 */

	/*
	 * If the original row was inserted by our own transaction, we must fire
	 * the trigger whether or not the keys are equal.  This is because our
	 * UPDATE will invalidate the INSERT so that the INSERT RI trigger will
	 * not do anything; so we had better do the UPDATE check.  (We could skip
	 * this if we knew the INSERT trigger already fired, but there is no easy
	 * way to know that.)
	 */
	xminDatum = slot_getsysattr(oldslot, MinTransactionIdAttributeNumber, &isnull);
	Assert(!isnull);
	xmin = DatumGetTransactionId(xminDatum);
	if (TransactionIdIsCurrentTransactionId(xmin))
		return true;

	/* If all old and new key values are equal, no check is needed */
	if (ri_KeysEqual(fk_rel, oldslot, newslot, riinfo, false))
		return false;

	/* Else we need to fire the trigger. */
	return true;
}