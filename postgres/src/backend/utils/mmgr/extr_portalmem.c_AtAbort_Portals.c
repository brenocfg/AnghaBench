#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ status; scalar_t__ createSubid; int /*<<< orphan*/  portalContext; int /*<<< orphan*/ * resowner; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;scalar_t__ autoHeld; } ;
struct TYPE_7__ {TYPE_2__* portal; } ;
typedef  TYPE_1__ PortalHashEnt ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 scalar_t__ InvalidSubTransactionId ; 
 int /*<<< orphan*/  MarkPortalFailed (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextDeleteChildren (int /*<<< orphan*/ ) ; 
 scalar_t__ PORTAL_ACTIVE ; 
 scalar_t__ PORTAL_READY ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/  (*) (TYPE_2__*)) ; 
 int /*<<< orphan*/  PortalHashTable ; 
 int /*<<< orphan*/  PortalReleaseCachedPlan (TYPE_2__*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 scalar_t__ shmem_exit_inprogress ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
AtAbort_Portals(void)
{
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	hash_seq_init(&status, PortalHashTable);

	while ((hentry = (PortalHashEnt *) hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		/*
		 * When elog(FATAL) is progress, we need to set the active portal to
		 * failed, so that PortalCleanup() doesn't run the executor shutdown.
		 */
		if (portal->status == PORTAL_ACTIVE && shmem_exit_inprogress)
			MarkPortalFailed(portal);

		/*
		 * Do nothing else to cursors held over from a previous transaction.
		 */
		if (portal->createSubid == InvalidSubTransactionId)
			continue;

		/*
		 * Do nothing to auto-held cursors.  This is similar to the case of a
		 * cursor from a previous transaction, but it could also be that the
		 * cursor was auto-held in this transaction, so it wants to live on.
		 */
		if (portal->autoHeld)
			continue;

		/*
		 * If it was created in the current transaction, we can't do normal
		 * shutdown on a READY portal either; it might refer to objects
		 * created in the failed transaction.  See comments in
		 * AtSubAbort_Portals.
		 */
		if (portal->status == PORTAL_READY)
			MarkPortalFailed(portal);

		/*
		 * Allow portalcmds.c to clean up the state it knows about, if we
		 * haven't already.
		 */
		if (PointerIsValid(portal->cleanup))
		{
			portal->cleanup(portal);
			portal->cleanup = NULL;
		}

		/* drop cached plan reference, if any */
		PortalReleaseCachedPlan(portal);

		/*
		 * Any resources belonging to the portal will be released in the
		 * upcoming transaction-wide cleanup; they will be gone before we run
		 * PortalDrop.
		 */
		portal->resowner = NULL;

		/*
		 * Although we can't delete the portal data structure proper, we can
		 * release any memory in subsidiary contexts, such as executor state.
		 * The cleanup hook was the last thing that might have needed data
		 * there.  But leave active portals alone.
		 */
		if (portal->status != PORTAL_ACTIVE)
			MemoryContextDeleteChildren(portal->portalContext);
	}
}