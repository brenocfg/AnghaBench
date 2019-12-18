#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t freed_segment_counter; TYPE_1__* control; } ;
typedef  TYPE_2__ dsa_area ;
struct TYPE_6__ {size_t freed_segment_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_AREA_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  check_for_freed_segments_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  pg_read_barrier () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
check_for_freed_segments(dsa_area *area)
{
	size_t		freed_segment_counter;

	/*
	 * Any other process that has freed a segment has incremented
	 * freed_segment_counter while holding an LWLock, and that must precede
	 * any backend creating a new segment in the same slot while holding an
	 * LWLock, and that must precede the creation of any dsa_pointer pointing
	 * into the new segment which might reach us here, and the caller must
	 * have sent the dsa_pointer to this process using appropriate memory
	 * synchronization (some kind of locking or atomic primitive or system
	 * call).  So all we need to do on the reading side is ask for the load of
	 * freed_segment_counter to follow the caller's load of the dsa_pointer it
	 * has, and we can be sure to detect any segments that had been freed as
	 * of the time that the dsa_pointer reached this process.
	 */
	pg_read_barrier();
	freed_segment_counter = area->control->freed_segment_counter;
	if (unlikely(area->freed_segment_counter != freed_segment_counter))
	{
		/* Check all currently mapped segments to find what's been freed. */
		LWLockAcquire(DSA_AREA_LOCK(area), LW_EXCLUSIVE);
		check_for_freed_segments_locked(area);
		LWLockRelease(DSA_AREA_LOCK(area));
	}
}