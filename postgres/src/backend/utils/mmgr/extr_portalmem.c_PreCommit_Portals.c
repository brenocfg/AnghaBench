#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ status; int cursorOptions; scalar_t__ createSubid; int /*<<< orphan*/ * resowner; int /*<<< orphan*/ * holdSnapshot; int /*<<< orphan*/  autoHeld; scalar_t__ portalPinned; } ;
struct TYPE_5__ {TYPE_2__* portal; } ;
typedef  TYPE_1__ PortalHashEnt ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int CURSOR_OPT_HOLD ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HoldPortal (TYPE_2__*) ; 
 scalar_t__ InvalidSubTransactionId ; 
 scalar_t__ PORTAL_ACTIVE ; 
 scalar_t__ PORTAL_READY ; 
 int /*<<< orphan*/  PortalDrop (TYPE_2__*,int) ; 
 int /*<<< orphan*/  PortalHashTable ; 
 int /*<<< orphan*/  UnregisterSnapshotFromOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_term (int /*<<< orphan*/ *) ; 

bool
PreCommit_Portals(bool isPrepare)
{
	bool		result = false;
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	hash_seq_init(&status, PortalHashTable);

	while ((hentry = (PortalHashEnt *) hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		/*
		 * There should be no pinned portals anymore. Complain if someone
		 * leaked one. Auto-held portals are allowed; we assume that whoever
		 * pinned them is managing them.
		 */
		if (portal->portalPinned && !portal->autoHeld)
			elog(ERROR, "cannot commit while a portal is pinned");

		/*
		 * Do not touch active portals --- this can only happen in the case of
		 * a multi-transaction utility command, such as VACUUM, or a commit in
		 * a procedure.
		 *
		 * Note however that any resource owner attached to such a portal is
		 * still going to go away, so don't leave a dangling pointer.  Also
		 * unregister any snapshots held by the portal, mainly to avoid
		 * snapshot leak warnings from ResourceOwnerRelease().
		 */
		if (portal->status == PORTAL_ACTIVE)
		{
			if (portal->holdSnapshot)
			{
				if (portal->resowner)
					UnregisterSnapshotFromOwner(portal->holdSnapshot,
												portal->resowner);
				portal->holdSnapshot = NULL;
			}
			portal->resowner = NULL;
			continue;
		}

		/* Is it a holdable portal created in the current xact? */
		if ((portal->cursorOptions & CURSOR_OPT_HOLD) &&
			portal->createSubid != InvalidSubTransactionId &&
			portal->status == PORTAL_READY)
		{
			/*
			 * We are exiting the transaction that created a holdable cursor.
			 * Instead of dropping the portal, prepare it for access by later
			 * transactions.
			 *
			 * However, if this is PREPARE TRANSACTION rather than COMMIT,
			 * refuse PREPARE, because the semantics seem pretty unclear.
			 */
			if (isPrepare)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("cannot PREPARE a transaction that has created a cursor WITH HOLD")));

			HoldPortal(portal);

			/* Report we changed state */
			result = true;
		}
		else if (portal->createSubid == InvalidSubTransactionId)
		{
			/*
			 * Do nothing to cursors held over from a previous transaction
			 * (including ones we just froze in a previous cycle of this loop)
			 */
			continue;
		}
		else
		{
			/* Zap all non-holdable portals */
			PortalDrop(portal, true);

			/* Report we changed state */
			result = true;
		}

		/*
		 * After either freezing or dropping a portal, we have to restart the
		 * iteration, because we could have invoked user-defined code that
		 * caused a drop of the next portal in the hash chain.
		 */
		hash_seq_term(&status);
		hash_seq_init(&status, PortalHashTable);
	}

	return result;
}