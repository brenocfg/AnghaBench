#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  (* rDestroy ) (TYPE_3__*) ;} ;
struct TYPE_16__ {scalar_t__ createSubid; int portalPos; int /*<<< orphan*/ * portalContext; int /*<<< orphan*/  status; int /*<<< orphan*/ * holdStore; scalar_t__ atEnd; int /*<<< orphan*/ * holdContext; TYPE_1__* queryDesc; scalar_t__ resowner; int /*<<< orphan*/  tupDesc; int /*<<< orphan*/ * holdSnapshot; } ;
struct TYPE_15__ {TYPE_3__* dest; int /*<<< orphan*/  snapshot; } ;
typedef  scalar_t__ ResourceOwner ;
typedef  TYPE_1__ QueryDesc ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/ * MemoryContext ;

/* Variables and functions */
 TYPE_2__* ActivePortal ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__* CreateDestReceiver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTupleDescCopy (int /*<<< orphan*/ ) ; 
 scalar_t__ CurrentResourceOwner ; 
 int /*<<< orphan*/  DestTuplestore ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecutorEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecutorFinish (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecutorRewind (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecutorRun (TYPE_1__*,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeQueryDesc (TYPE_1__*) ; 
 scalar_t__ InvalidSubTransactionId ; 
 int /*<<< orphan*/  MarkPortalActive (TYPE_2__*) ; 
 int /*<<< orphan*/  MarkPortalFailed (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextDeleteChildren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PORTAL_READY ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/ * PortalContext ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTuplestoreDestReceiverParams (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  tuplestore_rescan (int /*<<< orphan*/ *) ; 
 scalar_t__ tuplestore_skiptuples (int /*<<< orphan*/ *,int,int) ; 

void
PersistHoldablePortal(Portal portal)
{
	QueryDesc  *queryDesc = portal->queryDesc;
	Portal		saveActivePortal;
	ResourceOwner saveResourceOwner;
	MemoryContext savePortalContext;
	MemoryContext oldcxt;

	/*
	 * If we're preserving a holdable portal, we had better be inside the
	 * transaction that originally created it.
	 */
	Assert(portal->createSubid != InvalidSubTransactionId);
	Assert(queryDesc != NULL);

	/*
	 * Caller must have created the tuplestore already ... but not a snapshot.
	 */
	Assert(portal->holdContext != NULL);
	Assert(portal->holdStore != NULL);
	Assert(portal->holdSnapshot == NULL);

	/*
	 * Before closing down the executor, we must copy the tupdesc into
	 * long-term memory, since it was created in executor memory.
	 */
	oldcxt = MemoryContextSwitchTo(portal->holdContext);

	portal->tupDesc = CreateTupleDescCopy(portal->tupDesc);

	MemoryContextSwitchTo(oldcxt);

	/*
	 * Check for improper portal use, and mark portal active.
	 */
	MarkPortalActive(portal);

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

		MemoryContextSwitchTo(PortalContext);

		PushActiveSnapshot(queryDesc->snapshot);

		/*
		 * Rewind the executor: we need to store the entire result set in the
		 * tuplestore, so that subsequent backward FETCHs can be processed.
		 */
		ExecutorRewind(queryDesc);

		/*
		 * Change the destination to output to the tuplestore.  Note we tell
		 * the tuplestore receiver to detoast all data passed through it; this
		 * makes it safe to not keep a snapshot associated with the data.
		 */
		queryDesc->dest = CreateDestReceiver(DestTuplestore);
		SetTuplestoreDestReceiverParams(queryDesc->dest,
										portal->holdStore,
										portal->holdContext,
										true);

		/* Fetch the result set into the tuplestore */
		ExecutorRun(queryDesc, ForwardScanDirection, 0L, false);

		queryDesc->dest->rDestroy(queryDesc->dest);
		queryDesc->dest = NULL;

		/*
		 * Now shut down the inner executor.
		 */
		portal->queryDesc = NULL;	/* prevent double shutdown */
		ExecutorFinish(queryDesc);
		ExecutorEnd(queryDesc);
		FreeQueryDesc(queryDesc);

		/*
		 * Set the position in the result set.
		 */
		MemoryContextSwitchTo(portal->holdContext);

		if (portal->atEnd)
		{
			/*
			 * Just force the tuplestore forward to its end.  The size of the
			 * skip request here is arbitrary.
			 */
			while (tuplestore_skiptuples(portal->holdStore, 1000000, true))
				 /* continue */ ;
		}
		else
		{
			tuplestore_rescan(portal->holdStore);

			if (!tuplestore_skiptuples(portal->holdStore,
									   portal->portalPos,
									   true))
				elog(ERROR, "unexpected end of tuple stream");
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

	MemoryContextSwitchTo(oldcxt);

	/* Mark portal not active */
	portal->status = PORTAL_READY;

	ActivePortal = saveActivePortal;
	CurrentResourceOwner = saveResourceOwner;
	PortalContext = savePortalContext;

	PopActiveSnapshot();

	/*
	 * We can now release any subsidiary memory of the portal's context; we'll
	 * never use it again.  The executor already dropped its context, but this
	 * will clean up anything that glommed onto the portal's context via
	 * PortalContext.
	 */
	MemoryContextDeleteChildren(portal->portalContext);
}