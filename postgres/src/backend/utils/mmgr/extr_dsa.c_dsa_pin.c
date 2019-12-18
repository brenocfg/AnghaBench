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
struct TYPE_6__ {TYPE_1__* control; } ;
typedef  TYPE_2__ dsa_area ;
struct TYPE_5__ {int pinned; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_AREA_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
dsa_pin(dsa_area *area)
{
	LWLockAcquire(DSA_AREA_LOCK(area), LW_EXCLUSIVE);
	if (area->control->pinned)
	{
		LWLockRelease(DSA_AREA_LOCK(area));
		elog(ERROR, "dsa_area already pinned");
	}
	area->control->pinned = true;
	++area->control->refcnt;
	LWLockRelease(DSA_AREA_LOCK(area));
}