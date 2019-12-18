#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stmts; int /*<<< orphan*/ * cplan; } ;
typedef  TYPE_1__* Portal ;

/* Variables and functions */
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  ReleaseCachedPlan (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
PortalReleaseCachedPlan(Portal portal)
{
	if (portal->cplan)
	{
		ReleaseCachedPlan(portal->cplan, false);
		portal->cplan = NULL;

		/*
		 * We must also clear portal->stmts which is now a dangling reference
		 * to the cached plan's plan list.  This protects any code that might
		 * try to examine the Portal later.
		 */
		portal->stmts = NIL;
	}
}