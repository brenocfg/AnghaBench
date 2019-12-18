#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int Anum_pg_subscription_rel_srsublsn ; 
 int Anum_pg_subscription_rel_srsubstate ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int CharGetDatum (char) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int LSNGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  LockSharedObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Natts_pg_subscription_rel ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SUBSCRIPTIONRELMAP ; 
 TYPE_1__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubscriptionRelRelationId ; 
 int /*<<< orphan*/  SubscriptionRelationId ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
UpdateSubscriptionRelState(Oid subid, Oid relid, char state,
						   XLogRecPtr sublsn)
{
	Relation	rel;
	HeapTuple	tup;
	bool		nulls[Natts_pg_subscription_rel];
	Datum		values[Natts_pg_subscription_rel];
	bool		replaces[Natts_pg_subscription_rel];

	LockSharedObject(SubscriptionRelationId, subid, 0, AccessShareLock);

	rel = table_open(SubscriptionRelRelationId, RowExclusiveLock);

	/* Try finding existing mapping. */
	tup = SearchSysCacheCopy2(SUBSCRIPTIONRELMAP,
							  ObjectIdGetDatum(relid),
							  ObjectIdGetDatum(subid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "subscription table %u in subscription %u does not exist",
			 relid, subid);

	/* Update the tuple. */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));
	memset(replaces, false, sizeof(replaces));

	replaces[Anum_pg_subscription_rel_srsubstate - 1] = true;
	values[Anum_pg_subscription_rel_srsubstate - 1] = CharGetDatum(state);

	replaces[Anum_pg_subscription_rel_srsublsn - 1] = true;
	if (sublsn != InvalidXLogRecPtr)
		values[Anum_pg_subscription_rel_srsublsn - 1] = LSNGetDatum(sublsn);
	else
		nulls[Anum_pg_subscription_rel_srsublsn - 1] = true;

	tup = heap_modify_tuple(tup, RelationGetDescr(rel), values, nulls,
							replaces);

	/* Update the catalog. */
	CatalogTupleUpdate(rel, &tup->t_self, tup);

	/* Cleanup. */
	table_close(rel, NoLock);
}