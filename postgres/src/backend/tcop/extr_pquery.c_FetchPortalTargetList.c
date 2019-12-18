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
struct TYPE_4__ {scalar_t__ strategy; } ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * FetchStatementTargetList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ PORTAL_MULTI_QUERY ; 
 scalar_t__ PortalGetPrimaryStmt (TYPE_1__*) ; 

List *
FetchPortalTargetList(Portal portal)
{
	/* no point in looking if we determined it doesn't return tuples */
	if (portal->strategy == PORTAL_MULTI_QUERY)
		return NIL;
	/* get the primary statement and find out what it returns */
	return FetchStatementTargetList((Node *) PortalGetPrimaryStmt(portal));
}