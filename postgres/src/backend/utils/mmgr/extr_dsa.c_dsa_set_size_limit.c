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
struct TYPE_5__ {size_t max_total_segment_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_AREA_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 

void
dsa_set_size_limit(dsa_area *area, size_t limit)
{
	LWLockAcquire(DSA_AREA_LOCK(area), LW_EXCLUSIVE);
	area->control->max_total_segment_size = limit;
	LWLockRelease(DSA_AREA_LOCK(area));
}