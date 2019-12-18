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
struct TYPE_2__ {scalar_t__ freeoffset; scalar_t__ totalsize; } ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHELINEALIGN (void*) ; 
 scalar_t__ ShmemBase ; 
 int /*<<< orphan*/  ShmemLock ; 
 TYPE_1__* ShmemSegHdr ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ ) ; 

void *
ShmemAllocNoError(Size size)
{
	Size		newStart;
	Size		newFree;
	void	   *newSpace;

	/*
	 * Ensure all space is adequately aligned.  We used to only MAXALIGN this
	 * space but experience has proved that on modern systems that is not good
	 * enough.  Many parts of the system are very sensitive to critical data
	 * structures getting split across cache line boundaries.  To avoid that,
	 * attempt to align the beginning of the allocation to a cache line
	 * boundary.  The calling code will still need to be careful about how it
	 * uses the allocated space - e.g. by padding each element in an array of
	 * structures out to a power-of-two size - but without this, even that
	 * won't be sufficient.
	 */
	size = CACHELINEALIGN(size);

	Assert(ShmemSegHdr != NULL);

	SpinLockAcquire(ShmemLock);

	newStart = ShmemSegHdr->freeoffset;

	newFree = newStart + size;
	if (newFree <= ShmemSegHdr->totalsize)
	{
		newSpace = (void *) ((char *) ShmemBase + newStart);
		ShmemSegHdr->freeoffset = newFree;
	}
	else
		newSpace = NULL;

	SpinLockRelease(ShmemLock);

	/* note this assert is okay with newSpace == NULL */
	Assert(newSpace == (void *) CACHELINEALIGN(newSpace));

	return newSpace;
}