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
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MAXALIGN (void*) ; 
 scalar_t__ ShmemBase ; 
 TYPE_1__* ShmemSegHdr ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 

void *
ShmemAllocUnlocked(Size size)
{
	Size		newStart;
	Size		newFree;
	void	   *newSpace;

	/*
	 * Ensure allocated space is adequately aligned.
	 */
	size = MAXALIGN(size);

	Assert(ShmemSegHdr != NULL);

	newStart = ShmemSegHdr->freeoffset;

	newFree = newStart + size;
	if (newFree > ShmemSegHdr->totalsize)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of shared memory (%zu bytes requested)",
						size)));
	ShmemSegHdr->freeoffset = newFree;

	newSpace = (void *) ((char *) ShmemBase + newStart);

	Assert(newSpace == (void *) MAXALIGN(newSpace));

	return newSpace;
}