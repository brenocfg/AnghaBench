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
struct TYPE_2__ {int /*<<< orphan*/  oldestMultiXactDB; int /*<<< orphan*/  oldestMultiXactId; int /*<<< orphan*/  nextOffset; int /*<<< orphan*/  nextMXact; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MultiXactOffset ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  MultiXactGenLock ; 
 TYPE_1__* MultiXactState ; 
 int /*<<< orphan*/  debug_elog6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
MultiXactGetCheckptMulti(bool is_shutdown,
						 MultiXactId *nextMulti,
						 MultiXactOffset *nextMultiOffset,
						 MultiXactId *oldestMulti,
						 Oid *oldestMultiDB)
{
	LWLockAcquire(MultiXactGenLock, LW_SHARED);
	*nextMulti = MultiXactState->nextMXact;
	*nextMultiOffset = MultiXactState->nextOffset;
	*oldestMulti = MultiXactState->oldestMultiXactId;
	*oldestMultiDB = MultiXactState->oldestMultiXactDB;
	LWLockRelease(MultiXactGenLock);

	debug_elog6(DEBUG2,
				"MultiXact: checkpoint is nextMulti %u, nextOffset %u, oldestMulti %u in DB %u",
				*nextMulti, *nextMultiOffset, *oldestMulti, *oldestMultiDB);
}