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

/* Variables and functions */
 void* InvalidMultiXactId ; 
 int /*<<< orphan*/  MXactCache ; 
 scalar_t__ MXactCacheMembers ; 
 int /*<<< orphan*/ * MXactContext ; 
 size_t MyBackendId ; 
 void** OldestMemberMXactId ; 
 void** OldestVisibleMXactId ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 

void
AtEOXact_MultiXact(void)
{
	/*
	 * Reset our OldestMemberMXactId and OldestVisibleMXactId values, both of
	 * which should only be valid while within a transaction.
	 *
	 * We assume that storing a MultiXactId is atomic and so we need not take
	 * MultiXactGenLock to do this.
	 */
	OldestMemberMXactId[MyBackendId] = InvalidMultiXactId;
	OldestVisibleMXactId[MyBackendId] = InvalidMultiXactId;

	/*
	 * Discard the local MultiXactId cache.  Since MXactContext was created as
	 * a child of TopTransactionContext, we needn't delete it explicitly.
	 */
	MXactContext = NULL;
	dlist_init(&MXactCache);
	MXactCacheMembers = 0;
}