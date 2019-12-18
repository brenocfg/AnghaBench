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
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  activeSubid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Portal ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 scalar_t__ PORTAL_ACTIVE ; 
 scalar_t__ PORTAL_READY ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

void
MarkPortalActive(Portal portal)
{
	/* For safety, this is a runtime test not just an Assert */
	if (portal->status != PORTAL_READY)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("portal \"%s\" cannot be run", portal->name)));
	/* Perform the state transition */
	portal->status = PORTAL_ACTIVE;
	portal->activeSubid = GetCurrentSubTransactionId();
}