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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  PGSharedMemoryDetach () ; 
 int /*<<< orphan*/ * ShmemProtectiveRegion ; 
 int /*<<< orphan*/ * UsedShmemSegAddr ; 

void
PGSharedMemoryNoReAttach(void)
{
	Assert(ShmemProtectiveRegion != NULL);
	Assert(UsedShmemSegAddr != NULL);
	Assert(IsUnderPostmaster);

	/*
	 * Under Windows we will not have mapped the segment, so we don't need to
	 * un-map it.  Just reset UsedShmemSegAddr to show we're not attached.
	 */
	UsedShmemSegAddr = NULL;

	/*
	 * We *must* close the inherited shmem segment handle, else Windows will
	 * consider the existence of this process to mean it can't release the
	 * shmem segment yet.  We can now use PGSharedMemoryDetach to do that.
	 */
	PGSharedMemoryDetach();
}