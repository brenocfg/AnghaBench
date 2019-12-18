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
struct TYPE_3__ {scalar_t__ owner_pid; int is_set; } ;
typedef  TYPE_1__ Latch ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  pg_memory_barrier () ; 

void
ResetLatch(Latch *latch)
{
	/* Only the owner should reset the latch */
	Assert(latch->owner_pid == MyProcPid);

	latch->is_set = false;

	/*
	 * Ensure that the write to is_set gets flushed to main memory before we
	 * examine any flag variables.  Otherwise a concurrent SetLatch might
	 * falsely conclude that it needn't signal us, even though we have missed
	 * seeing some flag updates that SetLatch was supposed to inform us of.
	 */
	pg_memory_barrier();
}