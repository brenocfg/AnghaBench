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
struct TYPE_9__ {scalar_t__ status; scalar_t__ portalContext; scalar_t__ holdContext; int /*<<< orphan*/ * holdStore; int /*<<< orphan*/ * resowner; int /*<<< orphan*/ * holdSnapshot; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;int /*<<< orphan*/  name; scalar_t__ portalPinned; } ;
typedef  TYPE_1__* Portal ;
typedef  scalar_t__ MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_CURSOR_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextDelete (scalar_t__) ; 
 scalar_t__ MemoryContextSwitchTo (scalar_t__) ; 
 scalar_t__ PORTAL_ACTIVE ; 
 scalar_t__ PORTAL_FAILED ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  PortalHashTableDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  PortalIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  PortalReleaseCachedPlan (TYPE_1__*) ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  ResourceOwnerDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceOwnerRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UnregisterSnapshotFromOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tuplestore_end (int /*<<< orphan*/ *) ; 

void
PortalDrop(Portal portal, bool isTopCommit)
{
	AssertArg(PortalIsValid(portal));

	/*
	 * Don't allow dropping a pinned portal, it's still needed by whoever
	 * pinned it.
	 */
	if (portal->portalPinned)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_CURSOR_STATE),
				 errmsg("cannot drop pinned portal \"%s\"", portal->name)));

	/*
	 * Not sure if the PORTAL_ACTIVE case can validly happen or not...
	 */
	if (portal->status == PORTAL_ACTIVE)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_CURSOR_STATE),
				 errmsg("cannot drop active portal \"%s\"", portal->name)));

	/*
	 * Allow portalcmds.c to clean up the state it knows about, in particular
	 * shutting down the executor if still active.  This step potentially runs
	 * user-defined code so failure has to be expected.  It's the cleanup
	 * hook's responsibility to not try to do that more than once, in the case
	 * that failure occurs and then we come back to drop the portal again
	 * during transaction abort.
	 *
	 * Note: in most paths of control, this will have been done already in
	 * MarkPortalDone or MarkPortalFailed.  We're just making sure.
	 */
	if (PointerIsValid(portal->cleanup))
	{
		portal->cleanup(portal);
		portal->cleanup = NULL;
	}

	/*
	 * Remove portal from hash table.  Because we do this here, we will not
	 * come back to try to remove the portal again if there's any error in the
	 * subsequent steps.  Better to leak a little memory than to get into an
	 * infinite error-recovery loop.
	 */
	PortalHashTableDelete(portal);

	/* drop cached plan reference, if any */
	PortalReleaseCachedPlan(portal);

	/*
	 * If portal has a snapshot protecting its data, release that.  This needs
	 * a little care since the registration will be attached to the portal's
	 * resowner; if the portal failed, we will already have released the
	 * resowner (and the snapshot) during transaction abort.
	 */
	if (portal->holdSnapshot)
	{
		if (portal->resowner)
			UnregisterSnapshotFromOwner(portal->holdSnapshot,
										portal->resowner);
		portal->holdSnapshot = NULL;
	}

	/*
	 * Release any resources still attached to the portal.  There are several
	 * cases being covered here:
	 *
	 * Top transaction commit (indicated by isTopCommit): normally we should
	 * do nothing here and let the regular end-of-transaction resource
	 * releasing mechanism handle these resources too.  However, if we have a
	 * FAILED portal (eg, a cursor that got an error), we'd better clean up
	 * its resources to avoid resource-leakage warning messages.
	 *
	 * Sub transaction commit: never comes here at all, since we don't kill
	 * any portals in AtSubCommit_Portals().
	 *
	 * Main or sub transaction abort: we will do nothing here because
	 * portal->resowner was already set NULL; the resources were already
	 * cleaned up in transaction abort.
	 *
	 * Ordinary portal drop: must release resources.  However, if the portal
	 * is not FAILED then we do not release its locks.  The locks become the
	 * responsibility of the transaction's ResourceOwner (since it is the
	 * parent of the portal's owner) and will be released when the transaction
	 * eventually ends.
	 */
	if (portal->resowner &&
		(!isTopCommit || portal->status == PORTAL_FAILED))
	{
		bool		isCommit = (portal->status != PORTAL_FAILED);

		ResourceOwnerRelease(portal->resowner,
							 RESOURCE_RELEASE_BEFORE_LOCKS,
							 isCommit, false);
		ResourceOwnerRelease(portal->resowner,
							 RESOURCE_RELEASE_LOCKS,
							 isCommit, false);
		ResourceOwnerRelease(portal->resowner,
							 RESOURCE_RELEASE_AFTER_LOCKS,
							 isCommit, false);
		ResourceOwnerDelete(portal->resowner);
	}
	portal->resowner = NULL;

	/*
	 * Delete tuplestore if present.  We should do this even under error
	 * conditions; since the tuplestore would have been using cross-
	 * transaction storage, its temp files need to be explicitly deleted.
	 */
	if (portal->holdStore)
	{
		MemoryContext oldcontext;

		oldcontext = MemoryContextSwitchTo(portal->holdContext);
		tuplestore_end(portal->holdStore);
		MemoryContextSwitchTo(oldcontext);
		portal->holdStore = NULL;
	}

	/* delete tuplestore storage, if any */
	if (portal->holdContext)
		MemoryContextDelete(portal->holdContext);

	/* release subsidiary storage */
	MemoryContextDelete(portal->portalContext);

	/* release portal struct (it's in TopPortalContext) */
	pfree(portal);
}