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

/* Variables and functions */
 int /*<<< orphan*/  DebugFileOpen () ; 
 int /*<<< orphan*/  InitBufferPoolAccess () ; 
 int /*<<< orphan*/  InitCommunication () ; 
 int /*<<< orphan*/  InitFileAccess () ; 
 int /*<<< orphan*/  InitSync () ; 
 int /*<<< orphan*/  smgrinit () ; 

void
BaseInit(void)
{
	/*
	 * Attach to shared memory and semaphores, and initialize our
	 * input/output/debugging file descriptors.
	 */
	InitCommunication();
	DebugFileOpen();

	/* Do local initialization of file, storage and buffer managers */
	InitFileAccess();
	InitSync();
	smgrinit();
	InitBufferPoolAccess();
}