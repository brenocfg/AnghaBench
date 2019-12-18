#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_9__ {int strategy; int /*<<< orphan*/  status; int /*<<< orphan*/  holdStore; int /*<<< orphan*/  portalContext; scalar_t__ resowner; int /*<<< orphan*/  run_once; } ;
typedef  scalar_t__ ResourceOwner ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FetchDirection ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 TYPE_1__* ActivePortal ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 scalar_t__ CurrentResourceOwner ; 
 int /*<<< orphan*/  DoPortalRunFetch (TYPE_1__*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FillPortalStore (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MarkPortalActive (TYPE_1__*) ; 
 int /*<<< orphan*/  MarkPortalFailed (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
#define  PORTAL_ONE_MOD_WITH 131 
#define  PORTAL_ONE_RETURNING 130 
#define  PORTAL_ONE_SELECT 129 
 int /*<<< orphan*/  PORTAL_READY ; 
#define  PORTAL_UTIL_SELECT 128 
 int /*<<< orphan*/  PortalContext ; 
 int /*<<< orphan*/  PortalIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

uint64
PortalRunFetch(Portal portal,
			   FetchDirection fdirection,
			   long count,
			   DestReceiver *dest)
{
	uint64		result;
	Portal		saveActivePortal;
	ResourceOwner saveResourceOwner;
	MemoryContext savePortalContext;
	MemoryContext oldContext;

	AssertArg(PortalIsValid(portal));

	/*
	 * Check for improper portal use, and mark portal active.
	 */
	MarkPortalActive(portal);

	/* If supporting FETCH, portal can't be run-once. */
	Assert(!portal->run_once);

	/*
	 * Set up global portal context pointers.
	 */
	saveActivePortal = ActivePortal;
	saveResourceOwner = CurrentResourceOwner;
	savePortalContext = PortalContext;
	PG_TRY();
	{
		ActivePortal = portal;
		if (portal->resowner)
			CurrentResourceOwner = portal->resowner;
		PortalContext = portal->portalContext;

		oldContext = MemoryContextSwitchTo(PortalContext);

		switch (portal->strategy)
		{
			case PORTAL_ONE_SELECT:
				result = DoPortalRunFetch(portal, fdirection, count, dest);
				break;

			case PORTAL_ONE_RETURNING:
			case PORTAL_ONE_MOD_WITH:
			case PORTAL_UTIL_SELECT:

				/*
				 * If we have not yet run the command, do so, storing its
				 * results in the portal's tuplestore.
				 */
				if (!portal->holdStore)
					FillPortalStore(portal, false /* isTopLevel */ );

				/*
				 * Now fetch desired portion of results.
				 */
				result = DoPortalRunFetch(portal, fdirection, count, dest);
				break;

			default:
				elog(ERROR, "unsupported portal strategy");
				result = 0;		/* keep compiler quiet */
				break;
		}
	}
	PG_CATCH();
	{
		/* Uncaught error while executing portal: mark it dead */
		MarkPortalFailed(portal);

		/* Restore global vars and propagate error */
		ActivePortal = saveActivePortal;
		CurrentResourceOwner = saveResourceOwner;
		PortalContext = savePortalContext;

		PG_RE_THROW();
	}
	PG_END_TRY();

	MemoryContextSwitchTo(oldContext);

	/* Mark portal not active */
	portal->status = PORTAL_READY;

	ActivePortal = saveActivePortal;
	CurrentResourceOwner = saveResourceOwner;
	PortalContext = savePortalContext;

	return result;
}