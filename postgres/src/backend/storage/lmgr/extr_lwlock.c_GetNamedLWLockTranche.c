#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ num_lwlocks; int /*<<< orphan*/  tranche_name; } ;
typedef  int /*<<< orphan*/  LWLockPadded ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * MainLWLockArray ; 
 int NUM_FIXED_LWLOCKS ; 
 TYPE_1__* NamedLWLockTrancheRequestArray ; 
 int NamedLWLockTrancheRequests ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

LWLockPadded *
GetNamedLWLockTranche(const char *tranche_name)
{
	int			lock_pos;
	int			i;

	/*
	 * Obtain the position of base address of LWLock belonging to requested
	 * tranche_name in MainLWLockArray.  LWLocks for named tranches are placed
	 * in MainLWLockArray after fixed locks.
	 */
	lock_pos = NUM_FIXED_LWLOCKS;
	for (i = 0; i < NamedLWLockTrancheRequests; i++)
	{
		if (strcmp(NamedLWLockTrancheRequestArray[i].tranche_name,
				   tranche_name) == 0)
			return &MainLWLockArray[lock_pos];

		lock_pos += NamedLWLockTrancheRequestArray[i].num_lwlocks;
	}

	if (i >= NamedLWLockTrancheRequests)
		elog(ERROR, "requested tranche is not registered");

	/* just to keep compiler quiet */
	return NULL;
}