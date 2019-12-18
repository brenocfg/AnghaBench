#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int trancheId; char* trancheName; } ;
struct TYPE_7__ {int num_lwlocks; int /*<<< orphan*/  tranche_name; } ;
typedef  TYPE_1__ NamedLWLockTrancheRequest ;
typedef  TYPE_2__ NamedLWLockTranche ;
typedef  TYPE_3__ LWLockPadded ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int) ; 
 int LWLockNewTrancheId () ; 
 int LWTRANCHE_BUFFER_MAPPING ; 
 int LWTRANCHE_LOCK_MANAGER ; 
 int LWTRANCHE_PREDICATE_LOCK_MANAGER ; 
 TYPE_3__* MainLWLockArray ; 
 int NUM_BUFFER_PARTITIONS ; 
 int NUM_FIXED_LWLOCKS ; 
 int NUM_INDIVIDUAL_LWLOCKS ; 
 int NUM_LOCK_PARTITIONS ; 
 int NUM_PREDICATELOCK_PARTITIONS ; 
 TYPE_2__* NamedLWLockTrancheArray ; 
 TYPE_1__* NamedLWLockTrancheRequestArray ; 
 int NamedLWLockTrancheRequests ; 
 int NumLWLocksByNamedTranches () ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
InitializeLWLocks(void)
{
	int			numNamedLocks = NumLWLocksByNamedTranches();
	int			id;
	int			i;
	int			j;
	LWLockPadded *lock;

	/* Initialize all individual LWLocks in main array */
	for (id = 0, lock = MainLWLockArray; id < NUM_INDIVIDUAL_LWLOCKS; id++, lock++)
		LWLockInitialize(&lock->lock, id);

	/* Initialize buffer mapping LWLocks in main array */
	lock = MainLWLockArray + NUM_INDIVIDUAL_LWLOCKS;
	for (id = 0; id < NUM_BUFFER_PARTITIONS; id++, lock++)
		LWLockInitialize(&lock->lock, LWTRANCHE_BUFFER_MAPPING);

	/* Initialize lmgrs' LWLocks in main array */
	lock = MainLWLockArray + NUM_INDIVIDUAL_LWLOCKS + NUM_BUFFER_PARTITIONS;
	for (id = 0; id < NUM_LOCK_PARTITIONS; id++, lock++)
		LWLockInitialize(&lock->lock, LWTRANCHE_LOCK_MANAGER);

	/* Initialize predicate lmgrs' LWLocks in main array */
	lock = MainLWLockArray + NUM_INDIVIDUAL_LWLOCKS +
		NUM_BUFFER_PARTITIONS + NUM_LOCK_PARTITIONS;
	for (id = 0; id < NUM_PREDICATELOCK_PARTITIONS; id++, lock++)
		LWLockInitialize(&lock->lock, LWTRANCHE_PREDICATE_LOCK_MANAGER);

	/* Initialize named tranches. */
	if (NamedLWLockTrancheRequests > 0)
	{
		char	   *trancheNames;

		NamedLWLockTrancheArray = (NamedLWLockTranche *)
			&MainLWLockArray[NUM_FIXED_LWLOCKS + numNamedLocks];

		trancheNames = (char *) NamedLWLockTrancheArray +
			(NamedLWLockTrancheRequests * sizeof(NamedLWLockTranche));
		lock = &MainLWLockArray[NUM_FIXED_LWLOCKS];

		for (i = 0; i < NamedLWLockTrancheRequests; i++)
		{
			NamedLWLockTrancheRequest *request;
			NamedLWLockTranche *tranche;
			char	   *name;

			request = &NamedLWLockTrancheRequestArray[i];
			tranche = &NamedLWLockTrancheArray[i];

			name = trancheNames;
			trancheNames += strlen(request->tranche_name) + 1;
			strcpy(name, request->tranche_name);
			tranche->trancheId = LWLockNewTrancheId();
			tranche->trancheName = name;

			for (j = 0; j < request->num_lwlocks; j++, lock++)
				LWLockInitialize(&lock->lock, tranche->trancheId);
		}
	}
}