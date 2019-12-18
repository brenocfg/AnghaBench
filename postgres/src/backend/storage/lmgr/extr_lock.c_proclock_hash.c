#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  myProc; TYPE_1__* myLock; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;
typedef  int Size ;
typedef  TYPE_2__ PROCLOCKTAG ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int LOG2_NUM_LOCK_PARTITIONS ; 
 int LockTagHashCode (int /*<<< orphan*/ *) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
proclock_hash(const void *key, Size keysize)
{
	const PROCLOCKTAG *proclocktag = (const PROCLOCKTAG *) key;
	uint32		lockhash;
	Datum		procptr;

	Assert(keysize == sizeof(PROCLOCKTAG));

	/* Look into the associated LOCK object, and compute its hash code */
	lockhash = LockTagHashCode(&proclocktag->myLock->tag);

	/*
	 * To make the hash code also depend on the PGPROC, we xor the proc
	 * struct's address into the hash code, left-shifted so that the
	 * partition-number bits don't change.  Since this is only a hash, we
	 * don't care if we lose high-order bits of the address; use an
	 * intermediate variable to suppress cast-pointer-to-int warnings.
	 */
	procptr = PointerGetDatum(proclocktag->myProc);
	lockhash ^= ((uint32) procptr) << LOG2_NUM_LOCK_PARTITIONS;

	return lockhash;
}