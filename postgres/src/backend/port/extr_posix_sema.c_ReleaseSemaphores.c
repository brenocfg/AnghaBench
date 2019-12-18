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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  PG_SEM_REF (scalar_t__) ; 
 int /*<<< orphan*/  PosixSemaphoreKill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mySemPointers ; 
 int numSems ; 
 scalar_t__ sharedSemas ; 

__attribute__((used)) static void
ReleaseSemaphores(int status, Datum arg)
{
	int			i;

#ifdef USE_NAMED_POSIX_SEMAPHORES
	for (i = 0; i < numSems; i++)
		PosixSemaphoreKill(mySemPointers[i]);
	free(mySemPointers);
#endif

#ifdef USE_UNNAMED_POSIX_SEMAPHORES
	for (i = 0; i < numSems; i++)
		PosixSemaphoreKill(PG_SEM_REF(sharedSemas + i));
#endif
}