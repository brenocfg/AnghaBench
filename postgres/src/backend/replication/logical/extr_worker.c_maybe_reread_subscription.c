#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  subid; } ;
struct TYPE_6__ {scalar_t__ dbid; int /*<<< orphan*/  synccommit; int /*<<< orphan*/  name; int /*<<< orphan*/  publications; int /*<<< orphan*/  slotname; int /*<<< orphan*/  conninfo; int /*<<< orphan*/  enabled; } ;
typedef  TYPE_1__ Subscription ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyContext ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeSubscription (TYPE_1__*) ; 
 TYPE_1__* GetSubscription (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_3__* MyLogicalRepWorker ; 
 TYPE_1__* MySubscription ; 
 int MySubscriptionValid ; 
 int /*<<< orphan*/  PGC_BACKEND ; 
 int /*<<< orphan*/  PGC_S_OVERRIDE ; 
 int /*<<< orphan*/  SetConfigOption (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maybe_reread_subscription(void)
{
	MemoryContext oldctx;
	Subscription *newsub;
	bool		started_tx = false;

	/* When cache state is valid there is nothing to do here. */
	if (MySubscriptionValid)
		return;

	/* This function might be called inside or outside of transaction. */
	if (!IsTransactionState())
	{
		StartTransactionCommand();
		started_tx = true;
	}

	/* Ensure allocations in permanent context. */
	oldctx = MemoryContextSwitchTo(ApplyContext);

	newsub = GetSubscription(MyLogicalRepWorker->subid, true);

	/*
	 * Exit if the subscription was removed. This normally should not happen
	 * as the worker gets killed during DROP SUBSCRIPTION.
	 */
	if (!newsub)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will "
						"stop because the subscription was removed",
						MySubscription->name)));

		proc_exit(0);
	}

	/*
	 * Exit if the subscription was disabled. This normally should not happen
	 * as the worker gets killed during ALTER SUBSCRIPTION ... DISABLE.
	 */
	if (!newsub->enabled)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will "
						"stop because the subscription was disabled",
						MySubscription->name)));

		proc_exit(0);
	}

	/*
	 * Exit if connection string was changed. The launcher will start new
	 * worker.
	 */
	if (strcmp(newsub->conninfo, MySubscription->conninfo) != 0)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will "
						"restart because the connection information was changed",
						MySubscription->name)));

		proc_exit(0);
	}

	/*
	 * Exit if subscription name was changed (it's used for
	 * fallback_application_name). The launcher will start new worker.
	 */
	if (strcmp(newsub->name, MySubscription->name) != 0)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will "
						"restart because subscription was renamed",
						MySubscription->name)));

		proc_exit(0);
	}

	/* !slotname should never happen when enabled is true. */
	Assert(newsub->slotname);

	/*
	 * We need to make new connection to new slot if slot name has changed so
	 * exit here as well if that's the case.
	 */
	if (strcmp(newsub->slotname, MySubscription->slotname) != 0)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will "
						"restart because the replication slot name was changed",
						MySubscription->name)));

		proc_exit(0);
	}

	/*
	 * Exit if publication list was changed. The launcher will start new
	 * worker.
	 */
	if (!equal(newsub->publications, MySubscription->publications))
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will "
						"restart because subscription's publications were changed",
						MySubscription->name)));

		proc_exit(0);
	}

	/* Check for other changes that should never happen too. */
	if (newsub->dbid != MySubscription->dbid)
	{
		elog(ERROR, "subscription %u changed unexpectedly",
			 MyLogicalRepWorker->subid);
	}

	/* Clean old subscription info and switch to new one. */
	FreeSubscription(MySubscription);
	MySubscription = newsub;

	MemoryContextSwitchTo(oldctx);

	/* Change synchronous commit according to the user's wishes */
	SetConfigOption("synchronous_commit", MySubscription->synccommit,
					PGC_BACKEND, PGC_S_OVERRIDE);

	if (started_tx)
		CommitTransactionCommand();

	MySubscriptionValid = true;
}