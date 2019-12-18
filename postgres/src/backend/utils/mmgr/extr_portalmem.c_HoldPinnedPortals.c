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
struct TYPE_5__ {int autoHeld; scalar_t__ strategy; scalar_t__ status; scalar_t__ portalPinned; } ;
struct TYPE_4__ {TYPE_2__* portal; } ;
typedef  TYPE_1__ PortalHashEnt ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TRANSACTION_TERMINATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HoldPortal (TYPE_2__*) ; 
 scalar_t__ PORTAL_ONE_SELECT ; 
 scalar_t__ PORTAL_READY ; 
 int /*<<< orphan*/  PortalHashTable ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 

void
HoldPinnedPortals(void)
{
	HASH_SEQ_STATUS status;
	PortalHashEnt *hentry;

	hash_seq_init(&status, PortalHashTable);

	while ((hentry = (PortalHashEnt *) hash_seq_search(&status)) != NULL)
	{
		Portal		portal = hentry->portal;

		if (portal->portalPinned && !portal->autoHeld)
		{
			/*
			 * Doing transaction control, especially abort, inside a cursor
			 * loop that is not read-only, for example using UPDATE ...
			 * RETURNING, has weird semantics issues.  Also, this
			 * implementation wouldn't work, because such portals cannot be
			 * held.  (The core grammar enforces that only SELECT statements
			 * can drive a cursor, but for example PL/pgSQL does not restrict
			 * it.)
			 */
			if (portal->strategy != PORTAL_ONE_SELECT)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TRANSACTION_TERMINATION),
						 errmsg("cannot perform transaction commands inside a cursor loop that is not read-only")));

			/* Verify it's in a suitable state to be held */
			if (portal->status != PORTAL_READY)
				elog(ERROR, "pinned portal is not ready to be auto-held");

			HoldPortal(portal);
			portal->autoHeld = true;
		}
	}
}