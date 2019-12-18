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
struct TYPE_6__ {int atStart; int atEnd; scalar_t__ portalPos; TYPE_1__* queryDesc; scalar_t__ holdStore; int /*<<< orphan*/  holdContext; } ;
struct TYPE_5__ {int /*<<< orphan*/  snapshot; } ;
typedef  TYPE_1__ QueryDesc ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecutorRewind (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_rescan (scalar_t__) ; 

__attribute__((used)) static void
DoPortalRewind(Portal portal)
{
	QueryDesc  *queryDesc;

	/* Rewind holdStore, if we have one */
	if (portal->holdStore)
	{
		MemoryContext oldcontext;

		oldcontext = MemoryContextSwitchTo(portal->holdContext);
		tuplestore_rescan(portal->holdStore);
		MemoryContextSwitchTo(oldcontext);
	}

	/* Rewind executor, if active */
	queryDesc = portal->queryDesc;
	if (queryDesc)
	{
		PushActiveSnapshot(queryDesc->snapshot);
		ExecutorRewind(queryDesc);
		PopActiveSnapshot();
	}

	portal->atStart = true;
	portal->atEnd = false;
	portal->portalPos = 0;
}