#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* conflictTab; } ;
typedef  TYPE_1__* LockMethod ;
typedef  size_t LOCKMODE ;

/* Variables and functions */
 size_t DEFAULT_LOCKMETHOD ; 
 int LOCKBIT_ON (size_t) ; 
 TYPE_1__** LockMethods ; 

bool
DoLockModesConflict(LOCKMODE mode1, LOCKMODE mode2)
{
	LockMethod	lockMethodTable = LockMethods[DEFAULT_LOCKMETHOD];

	if (lockMethodTable->conflictTab[mode1] & LOCKBIT_ON(mode2))
		return true;

	return false;
}