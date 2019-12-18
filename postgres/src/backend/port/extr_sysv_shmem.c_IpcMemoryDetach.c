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
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ shmdt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
IpcMemoryDetach(int status, Datum shmaddr)
{
	/* Detach System V shared memory block. */
	if (shmdt(DatumGetPointer(shmaddr)) < 0)
		elog(LOG, "shmdt(%p) failed: %m", DatumGetPointer(shmaddr));
}