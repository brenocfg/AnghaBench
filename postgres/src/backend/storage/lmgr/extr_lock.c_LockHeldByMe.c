#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  localtag ;
struct TYPE_5__ {scalar_t__ nLocks; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ LOCALLOCKTAG ;
typedef  TYPE_2__ LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  LockMethodLocalHash ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
LockHeldByMe(const LOCKTAG *locktag, LOCKMODE lockmode)
{
	LOCALLOCKTAG localtag;
	LOCALLOCK  *locallock;

	/*
	 * See if there is a LOCALLOCK entry for this lock and lockmode
	 */
	MemSet(&localtag, 0, sizeof(localtag)); /* must clear padding */
	localtag.lock = *locktag;
	localtag.mode = lockmode;

	locallock = (LOCALLOCK *) hash_search(LockMethodLocalHash,
										  (void *) &localtag,
										  HASH_FIND, NULL);

	return (locallock && locallock->nLocks > 0);
}