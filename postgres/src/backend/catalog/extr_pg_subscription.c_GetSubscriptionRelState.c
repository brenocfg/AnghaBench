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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_subscription_rel_srsublsn ; 
 int /*<<< orphan*/  Anum_pg_subscription_rel_srsubstate ; 
 int /*<<< orphan*/  Assert (int) ; 
 char DatumGetChar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 char SUBREL_STATE_UNKNOWN ; 
 int /*<<< orphan*/  SUBSCRIPTIONRELMAP ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubscriptionRelRelationId ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char
GetSubscriptionRelState(Oid subid, Oid relid, XLogRecPtr *sublsn,
						bool missing_ok)
{
	Relation	rel;
	HeapTuple	tup;
	char		substate;
	bool		isnull;
	Datum		d;

	rel = table_open(SubscriptionRelRelationId, AccessShareLock);

	/* Try finding the mapping. */
	tup = SearchSysCache2(SUBSCRIPTIONRELMAP,
						  ObjectIdGetDatum(relid),
						  ObjectIdGetDatum(subid));

	if (!HeapTupleIsValid(tup))
	{
		if (missing_ok)
		{
			table_close(rel, AccessShareLock);
			*sublsn = InvalidXLogRecPtr;
			return SUBREL_STATE_UNKNOWN;
		}

		elog(ERROR, "subscription table %u in subscription %u does not exist",
			 relid, subid);
	}

	/* Get the state. */
	d = SysCacheGetAttr(SUBSCRIPTIONRELMAP, tup,
						Anum_pg_subscription_rel_srsubstate, &isnull);
	Assert(!isnull);
	substate = DatumGetChar(d);
	d = SysCacheGetAttr(SUBSCRIPTIONRELMAP, tup,
						Anum_pg_subscription_rel_srsublsn, &isnull);
	if (isnull)
		*sublsn = InvalidXLogRecPtr;
	else
		*sublsn = DatumGetLSN(d);

	/* Cleanup */
	ReleaseSysCache(tup);
	table_close(rel, AccessShareLock);

	return substate;
}