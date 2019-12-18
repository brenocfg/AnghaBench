#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ status; int /*<<< orphan*/  (* cleanup ) (TYPE_1__*) ;} ;
typedef  TYPE_1__* Portal ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ PORTAL_ACTIVE ; 
 scalar_t__ PORTAL_DONE ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
MarkPortalDone(Portal portal)
{
	/* Perform the state transition */
	Assert(portal->status == PORTAL_ACTIVE);
	portal->status = PORTAL_DONE;

	/*
	 * Allow portalcmds.c to clean up the state it knows about.  We might as
	 * well do that now, since the portal can't be executed any more.
	 *
	 * In some cases involving execution of a ROLLBACK command in an already
	 * aborted transaction, this is necessary, or we'd reach AtCleanup_Portals
	 * with the cleanup hook still unexecuted.
	 */
	if (PointerIsValid(portal->cleanup))
	{
		portal->cleanup(portal);
		portal->cleanup = NULL;
	}
}