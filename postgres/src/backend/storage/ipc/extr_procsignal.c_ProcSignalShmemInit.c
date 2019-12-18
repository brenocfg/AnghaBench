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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  ProcSignalSlot ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcSignalShmemSize () ; 
 int /*<<< orphan*/ * ProcSignalSlots ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 

void
ProcSignalShmemInit(void)
{
	Size		size = ProcSignalShmemSize();
	bool		found;

	ProcSignalSlots = (ProcSignalSlot *)
		ShmemInitStruct("ProcSignalSlots", size, &found);

	/* If we're first, set everything to zeroes */
	if (!found)
		MemSet(ProcSignalSlots, 0, size);
}