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
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGSharedMemoryDetach () ; 
 scalar_t__ UsedShmemSegID ; 

__attribute__((used)) static void
pgwin32_SharedMemoryDelete(int status, Datum shmId)
{
	Assert(DatumGetPointer(shmId) == UsedShmemSegID);
	PGSharedMemoryDetach();
}