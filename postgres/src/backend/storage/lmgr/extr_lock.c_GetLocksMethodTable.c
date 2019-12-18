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
typedef  int /*<<< orphan*/  LockMethod ;
typedef  size_t LOCKMETHODID ;
typedef  int /*<<< orphan*/  LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t LOCK_LOCKMETHOD (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * LockMethods ; 
 size_t lengthof (int /*<<< orphan*/ *) ; 

LockMethod
GetLocksMethodTable(const LOCK *lock)
{
	LOCKMETHODID lockmethodid = LOCK_LOCKMETHOD(*lock);

	Assert(0 < lockmethodid && lockmethodid < lengthof(LockMethods));
	return LockMethods[lockmethodid];
}