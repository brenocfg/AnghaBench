#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_18__ {char* subname; int kind; char* conninfo; int /*<<< orphan*/  options; int /*<<< orphan*/  publication; } ;
struct TYPE_17__ {int /*<<< orphan*/  oid; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_15__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  publications; int /*<<< orphan*/  slotname; } ;
typedef  TYPE_1__ Subscription ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_subscription ;
typedef  int Datum ;
typedef  TYPE_4__ AlterSubscriptionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
#define  ALTER_SUBSCRIPTION_CONNECTION 132 
#define  ALTER_SUBSCRIPTION_ENABLED 131 
#define  ALTER_SUBSCRIPTION_OPTIONS 130 
#define  ALTER_SUBSCRIPTION_PUBLICATION 129 
#define  ALTER_SUBSCRIPTION_REFRESH 128 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AlterSubscription_refresh (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Anum_pg_subscription_subconninfo ; 
 int /*<<< orphan*/  Anum_pg_subscription_subenabled ; 
 int /*<<< orphan*/  Anum_pg_subscription_subpublications ; 
 int /*<<< orphan*/  Anum_pg_subscription_subslotname ; 
 int /*<<< orphan*/  Anum_pg_subscription_subsynccommit ; 
 int /*<<< orphan*/  ApplyLauncherWakeupAtCommit () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 TYPE_1__* GetSubscription (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockSharedObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int Natts_pg_subscription ; 
 int /*<<< orphan*/  OBJECT_SUBSCRIPTION ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SUBSCRIPTIONNAME ; 
 TYPE_2__* SearchSysCacheCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubscriptionRelationId ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  load_file (char*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namein ; 
 int /*<<< orphan*/  parse_subscription_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int*,char**,int*,char**,int*) ; 
 int /*<<< orphan*/  pg_subscription_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int publicationListToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walrcv_check_conninfo (char*) ; 

ObjectAddress
AlterSubscription(AlterSubscriptionStmt *stmt)
{
	Relation	rel;
	ObjectAddress myself;
	bool		nulls[Natts_pg_subscription];
	bool		replaces[Natts_pg_subscription];
	Datum		values[Natts_pg_subscription];
	HeapTuple	tup;
	Oid			subid;
	bool		update_tuple = false;
	Subscription *sub;
	Form_pg_subscription form;

	rel = table_open(SubscriptionRelationId, RowExclusiveLock);

	/* Fetch the existing tuple. */
	tup = SearchSysCacheCopy2(SUBSCRIPTIONNAME, MyDatabaseId,
							  CStringGetDatum(stmt->subname));

	if (!HeapTupleIsValid(tup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("subscription \"%s\" does not exist",
						stmt->subname)));

	form = (Form_pg_subscription) GETSTRUCT(tup);
	subid = form->oid;

	/* must be owner */
	if (!pg_subscription_ownercheck(subid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_SUBSCRIPTION,
					   stmt->subname);

	sub = GetSubscription(subid, false);

	/* Lock the subscription so nobody else can do anything with it. */
	LockSharedObject(SubscriptionRelationId, subid, 0, AccessExclusiveLock);

	/* Form a new tuple. */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));
	memset(replaces, false, sizeof(replaces));

	switch (stmt->kind)
	{
		case ALTER_SUBSCRIPTION_OPTIONS:
			{
				char	   *slotname;
				bool		slotname_given;
				char	   *synchronous_commit;

				parse_subscription_options(stmt->options, NULL, NULL, NULL,
										   NULL, &slotname_given, &slotname,
										   NULL, &synchronous_commit, NULL);

				if (slotname_given)
				{
					if (sub->enabled && !slotname)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("cannot set %s for enabled subscription",
										"slot_name = NONE")));

					if (slotname)
						values[Anum_pg_subscription_subslotname - 1] =
							DirectFunctionCall1(namein, CStringGetDatum(slotname));
					else
						nulls[Anum_pg_subscription_subslotname - 1] = true;
					replaces[Anum_pg_subscription_subslotname - 1] = true;
				}

				if (synchronous_commit)
				{
					values[Anum_pg_subscription_subsynccommit - 1] =
						CStringGetTextDatum(synchronous_commit);
					replaces[Anum_pg_subscription_subsynccommit - 1] = true;
				}

				update_tuple = true;
				break;
			}

		case ALTER_SUBSCRIPTION_ENABLED:
			{
				bool		enabled,
							enabled_given;

				parse_subscription_options(stmt->options, NULL,
										   &enabled_given, &enabled, NULL,
										   NULL, NULL, NULL, NULL, NULL);
				Assert(enabled_given);

				if (!sub->slotname && enabled)
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("cannot enable subscription that does not have a slot name")));

				values[Anum_pg_subscription_subenabled - 1] =
					BoolGetDatum(enabled);
				replaces[Anum_pg_subscription_subenabled - 1] = true;

				if (enabled)
					ApplyLauncherWakeupAtCommit();

				update_tuple = true;
				break;
			}

		case ALTER_SUBSCRIPTION_CONNECTION:
			/* Load the library providing us libpq calls. */
			load_file("libpqwalreceiver", false);
			/* Check the connection info string. */
			walrcv_check_conninfo(stmt->conninfo);

			values[Anum_pg_subscription_subconninfo - 1] =
				CStringGetTextDatum(stmt->conninfo);
			replaces[Anum_pg_subscription_subconninfo - 1] = true;
			update_tuple = true;
			break;

		case ALTER_SUBSCRIPTION_PUBLICATION:
			{
				bool		copy_data;
				bool		refresh;

				parse_subscription_options(stmt->options, NULL, NULL, NULL,
										   NULL, NULL, NULL, &copy_data,
										   NULL, &refresh);

				values[Anum_pg_subscription_subpublications - 1] =
					publicationListToArray(stmt->publication);
				replaces[Anum_pg_subscription_subpublications - 1] = true;

				update_tuple = true;

				/* Refresh if user asked us to. */
				if (refresh)
				{
					if (!sub->enabled)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("ALTER SUBSCRIPTION with refresh is not allowed for disabled subscriptions"),
								 errhint("Use ALTER SUBSCRIPTION ... SET PUBLICATION ... WITH (refresh = false).")));

					/* Make sure refresh sees the new list of publications. */
					sub->publications = stmt->publication;

					AlterSubscription_refresh(sub, copy_data);
				}

				break;
			}

		case ALTER_SUBSCRIPTION_REFRESH:
			{
				bool		copy_data;

				if (!sub->enabled)
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("ALTER SUBSCRIPTION ... REFRESH is not allowed for disabled subscriptions")));

				parse_subscription_options(stmt->options, NULL, NULL, NULL,
										   NULL, NULL, NULL, &copy_data,
										   NULL, NULL);

				AlterSubscription_refresh(sub, copy_data);

				break;
			}

		default:
			elog(ERROR, "unrecognized ALTER SUBSCRIPTION kind %d",
				 stmt->kind);
	}

	/* Update the catalog if needed. */
	if (update_tuple)
	{
		tup = heap_modify_tuple(tup, RelationGetDescr(rel), values, nulls,
								replaces);

		CatalogTupleUpdate(rel, &tup->t_self, tup);

		heap_freetuple(tup);
	}

	table_close(rel, RowExclusiveLock);

	ObjectAddressSet(myself, SubscriptionRelationId, subid);

	InvokeObjectPostAlterHook(SubscriptionRelationId, subid, 0);

	return myself;
}