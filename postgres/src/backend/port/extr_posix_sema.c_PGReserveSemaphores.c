#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {int /*<<< orphan*/  st_ino; } ;
typedef  int /*<<< orphan*/  sem_t ;
typedef  scalar_t__ PGSemaphore ;

/* Variables and functions */
 int /*<<< orphan*/  DataDir ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PGSemaphoreShmemSize (int) ; 
 int /*<<< orphan*/  ReleaseSemaphores ; 
 scalar_t__ ShmemAllocUnlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int maxSems ; 
 int /*<<< orphan*/ ** mySemPointers ; 
 int /*<<< orphan*/  nextSemKey ; 
 scalar_t__ numSems ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sharedSemas ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

void
PGReserveSemaphores(int maxSemas)
{
	struct stat statbuf;

	/*
	 * We use the data directory's inode number to seed the search for free
	 * semaphore keys.  This minimizes the odds of collision with other
	 * postmasters, while maximizing the odds that we will detect and clean up
	 * semaphores left over from a crashed postmaster in our own directory.
	 */
	if (stat(DataDir, &statbuf) < 0)
		ereport(FATAL,
				(errcode_for_file_access(),
				 errmsg("could not stat data directory \"%s\": %m",
						DataDir)));

#ifdef USE_NAMED_POSIX_SEMAPHORES
	mySemPointers = (sem_t **) malloc(maxSemas * sizeof(sem_t *));
	if (mySemPointers == NULL)
		elog(PANIC, "out of memory");
#else

	/*
	 * We must use ShmemAllocUnlocked(), since the spinlock protecting
	 * ShmemAlloc() won't be ready yet.  (This ordering is necessary when we
	 * are emulating spinlocks with semaphores.)
	 */
	sharedSemas = (PGSemaphore)
		ShmemAllocUnlocked(PGSemaphoreShmemSize(maxSemas));
#endif

	numSems = 0;
	maxSems = maxSemas;
	nextSemKey = statbuf.st_ino;

	on_shmem_exit(ReleaseSemaphores, 0);
}