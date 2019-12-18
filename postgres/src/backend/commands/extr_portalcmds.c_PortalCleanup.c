#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cleanup; scalar_t__ status; scalar_t__ resowner; int /*<<< orphan*/ * queryDesc; } ;
typedef  scalar_t__ ResourceOwner ;
typedef  int /*<<< orphan*/  QueryDesc ;
typedef  TYPE_1__* Portal ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 scalar_t__ CurrentResourceOwner ; 
 int /*<<< orphan*/  ExecutorEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecutorFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeQueryDesc (int /*<<< orphan*/ *) ; 
 scalar_t__ PORTAL_FAILED ; 
 int PortalIsValid (TYPE_1__*) ; 

void
PortalCleanup(Portal portal)
{
	QueryDesc  *queryDesc;

	/*
	 * sanity checks
	 */
	AssertArg(PortalIsValid(portal));
	AssertArg(portal->cleanup == PortalCleanup);

	/*
	 * Shut down executor, if still running.  We skip this during error abort,
	 * since other mechanisms will take care of releasing executor resources,
	 * and we can't be sure that ExecutorEnd itself wouldn't fail.
	 */
	queryDesc = portal->queryDesc;
	if (queryDesc)
	{
		/*
		 * Reset the queryDesc before anything else.  This prevents us from
		 * trying to shut down the executor twice, in case of an error below.
		 * The transaction abort mechanisms will take care of resource cleanup
		 * in such a case.
		 */
		portal->queryDesc = NULL;

		if (portal->status != PORTAL_FAILED)
		{
			ResourceOwner saveResourceOwner;

			/* We must make the portal's resource owner current */
			saveResourceOwner = CurrentResourceOwner;
			if (portal->resowner)
				CurrentResourceOwner = portal->resowner;

			ExecutorFinish(queryDesc);
			ExecutorEnd(queryDesc);
			FreeQueryDesc(queryDesc);

			CurrentResourceOwner = saveResourceOwner;
		}
	}
}