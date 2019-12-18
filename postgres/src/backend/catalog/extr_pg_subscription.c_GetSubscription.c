#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  subenabled; int /*<<< orphan*/  subowner; int /*<<< orphan*/  subname; int /*<<< orphan*/  subdbid; } ;
struct TYPE_4__ {int /*<<< orphan*/  publications; void* synccommit; int /*<<< orphan*/ * slotname; void* conninfo; int /*<<< orphan*/  enabled; int /*<<< orphan*/  owner; void* name; int /*<<< orphan*/  dbid; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ Subscription ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_subscription ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_subscription_subconninfo ; 
 int /*<<< orphan*/  Anum_pg_subscription_subpublications ; 
 int /*<<< orphan*/  Anum_pg_subscription_subslotname ; 
 int /*<<< orphan*/  Anum_pg_subscription_subsynccommit ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBSCRIPTIONOID ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 void* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 void* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textarray_to_stringlist (int /*<<< orphan*/ ) ; 

Subscription *
GetSubscription(Oid subid, bool missing_ok)
{
	HeapTuple	tup;
	Subscription *sub;
	Form_pg_subscription subform;
	Datum		datum;
	bool		isnull;

	tup = SearchSysCache1(SUBSCRIPTIONOID, ObjectIdGetDatum(subid));

	if (!HeapTupleIsValid(tup))
	{
		if (missing_ok)
			return NULL;

		elog(ERROR, "cache lookup failed for subscription %u", subid);
	}

	subform = (Form_pg_subscription) GETSTRUCT(tup);

	sub = (Subscription *) palloc(sizeof(Subscription));
	sub->oid = subid;
	sub->dbid = subform->subdbid;
	sub->name = pstrdup(NameStr(subform->subname));
	sub->owner = subform->subowner;
	sub->enabled = subform->subenabled;

	/* Get conninfo */
	datum = SysCacheGetAttr(SUBSCRIPTIONOID,
							tup,
							Anum_pg_subscription_subconninfo,
							&isnull);
	Assert(!isnull);
	sub->conninfo = TextDatumGetCString(datum);

	/* Get slotname */
	datum = SysCacheGetAttr(SUBSCRIPTIONOID,
							tup,
							Anum_pg_subscription_subslotname,
							&isnull);
	if (!isnull)
		sub->slotname = pstrdup(NameStr(*DatumGetName(datum)));
	else
		sub->slotname = NULL;

	/* Get synccommit */
	datum = SysCacheGetAttr(SUBSCRIPTIONOID,
							tup,
							Anum_pg_subscription_subsynccommit,
							&isnull);
	Assert(!isnull);
	sub->synccommit = TextDatumGetCString(datum);

	/* Get publications */
	datum = SysCacheGetAttr(SUBSCRIPTIONOID,
							tup,
							Anum_pg_subscription_subpublications,
							&isnull);
	Assert(!isnull);
	sub->publications = textarray_to_stringlist(DatumGetArrayTypeP(datum));

	ReleaseSysCache(tup);

	return sub;
}