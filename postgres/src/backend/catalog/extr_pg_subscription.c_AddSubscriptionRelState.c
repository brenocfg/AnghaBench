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
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int Anum_pg_subscription_rel_srrelid ; 
 int Anum_pg_subscription_rel_srsubid ; 
 int Anum_pg_subscription_rel_srsublsn ; 
 int Anum_pg_subscription_rel_srsubstate ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CharGetDatum (char) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int LSNGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  LockSharedObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Natts_pg_subscription_rel ; 
 int /*<<< orphan*/  NoLock ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SUBSCRIPTIONRELMAP ; 
 int /*<<< orphan*/  SearchSysCacheCopy2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SubscriptionRelRelationId ; 
 int /*<<< orphan*/  SubscriptionRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AddSubscriptionRelState(Oid subid, Oid relid, char state,
						XLogRecPtr sublsn)
{
	Relation	rel;
	HeapTuple	tup;
	bool		nulls[Natts_pg_subscription_rel];
	Datum		values[Natts_pg_subscription_rel];

	LockSharedObject(SubscriptionRelationId, subid, 0, AccessShareLock);

	rel = table_open(SubscriptionRelRelationId, RowExclusiveLock);

	/* Try finding existing mapping. */
	tup = SearchSysCacheCopy2(SUBSCRIPTIONRELMAP,
							  ObjectIdGetDatum(relid),
							  ObjectIdGetDatum(subid));
	if (HeapTupleIsValid(tup))
		elog(ERROR, "subscription table %u in subscription %u already exists",
			 relid, subid);

	/* Form the tuple. */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));
	values[Anum_pg_subscription_rel_srsubid - 1] = ObjectIdGetDatum(subid);
	values[Anum_pg_subscription_rel_srrelid - 1] = ObjectIdGetDatum(relid);
	values[Anum_pg_subscription_rel_srsubstate - 1] = CharGetDatum(state);
	if (sublsn != InvalidXLogRecPtr)
		values[Anum_pg_subscription_rel_srsublsn - 1] = LSNGetDatum(sublsn);
	else
		nulls[Anum_pg_subscription_rel_srsublsn - 1] = true;

	tup = heap_form_tuple(RelationGetDescr(rel), values, nulls);

	/* Insert tuple into catalog. */
	CatalogTupleInsert(rel, tup);

	heap_freetuple(tup);

	/* Cleanup. */
	table_close(rel, NoLock);
}