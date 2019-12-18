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
struct TYPE_2__ {int /*<<< orphan*/  tranche_name; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  NamedLWLockTranche ;
typedef  int /*<<< orphan*/  LWLockPadded ;

/* Variables and functions */
 scalar_t__ LWLOCK_PADDED_SIZE ; 
 int NUM_FIXED_LWLOCKS ; 
 TYPE_1__* NamedLWLockTrancheRequestArray ; 
 int NamedLWLockTrancheRequests ; 
 scalar_t__ NumLWLocksByNamedTranches () ; 
 scalar_t__ add_size (scalar_t__,scalar_t__) ; 
 int lock_named_request_allowed ; 
 scalar_t__ mul_size (int,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

Size
LWLockShmemSize(void)
{
	Size		size;
	int			i;
	int			numLocks = NUM_FIXED_LWLOCKS;

	numLocks += NumLWLocksByNamedTranches();

	/* Space for the LWLock array. */
	size = mul_size(numLocks, sizeof(LWLockPadded));

	/* Space for dynamic allocation counter, plus room for alignment. */
	size = add_size(size, sizeof(int) + LWLOCK_PADDED_SIZE);

	/* space for named tranches. */
	size = add_size(size, mul_size(NamedLWLockTrancheRequests, sizeof(NamedLWLockTranche)));

	/* space for name of each tranche. */
	for (i = 0; i < NamedLWLockTrancheRequests; i++)
		size = add_size(size, strlen(NamedLWLockTrancheRequestArray[i].tranche_name) + 1);

	/* Disallow named LWLocks' requests after startup */
	lock_named_request_allowed = false;

	return size;
}