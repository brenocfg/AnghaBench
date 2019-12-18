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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  ReleaseSemaphores ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int maxSems ; 
 int /*<<< orphan*/ * mySemSet ; 
 scalar_t__ numSems ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PGReserveSemaphores(int maxSemas)
{
	mySemSet = (HANDLE *) malloc(maxSemas * sizeof(HANDLE));
	if (mySemSet == NULL)
		elog(PANIC, "out of memory");
	numSems = 0;
	maxSems = maxSemas;

	on_shmem_exit(ReleaseSemaphores, 0);
}