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
struct TYPE_5__ {scalar_t__ status; scalar_t__ createSubid; int portalPinned; int /*<<< orphan*/ * cleanup; int /*<<< orphan*/  name; int /*<<< orphan*/ * resowner; scalar_t__ autoHeld; } ;
struct TYPE_4__ {TYPE_2__* portal; } ;
typedef  TYPE_1__ PortalHashEnt ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidSubTransactionId ; 
 scalar_t__ PORTAL_ACTIVE ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PortalDrop (TYPE_2__*,int) ; 
 int /*<<< orphan*/  PortalHashTable ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

void
AtCleanup_Portals(void)
{
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	hash_seq_init(&status, PortalHashTable);

	while ((hentry = (PortalHashEnt *) hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		/*
		 * Do not touch active portals --- this can only happen in the case of
		 * a multi-transaction command.
		 */
		if (portal->status == PORTAL_ACTIVE)
			continue;

		/*
		 * Do nothing to cursors held over from a previous transaction or
		 * auto-held ones.
		 */
		if (portal->createSubid == InvalidSubTransactionId || portal->autoHeld)
		{
			Assert(portal->status != PORTAL_ACTIVE);
			Assert(portal->resowner == NULL);
			continue;
		}

		/*
		 * If a portal is still pinned, forcibly unpin it. PortalDrop will not
		 * let us drop the portal otherwise. Whoever pinned the portal was
		 * interrupted by the abort too and won't try to use it anymore.
		 */
		if (portal->portalPinned)
			portal->portalPinned = false;

		/*
		 * We had better not call any user-defined code during cleanup, so if
		 * the cleanup hook hasn't been run yet, too bad; we'll just skip it.
		 */
		if (PointerIsValid(portal->cleanup))
		{
			elog(WARNING, "skipping cleanup for portal \"%s\"", portal->name);
			portal->cleanup = NULL;
		}

		/* Zap it. */
		PortalDrop(portal, false);
	}
}