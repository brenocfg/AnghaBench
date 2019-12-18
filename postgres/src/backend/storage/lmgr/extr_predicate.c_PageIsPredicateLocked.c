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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  dbNode; } ;
struct TYPE_5__ {int /*<<< orphan*/  rd_id; TYPE_1__ rd_node; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGET ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/ * PredicateLockHashPartitionLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockTargetHash ; 
 int /*<<< orphan*/  PredicateLockTargetTagHashCode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_PAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
PageIsPredicateLocked(Relation relation, BlockNumber blkno)
{
	PREDICATELOCKTARGETTAG targettag;
	uint32		targettaghash;
	LWLock	   *partitionLock;
	PREDICATELOCKTARGET *target;

	SET_PREDICATELOCKTARGETTAG_PAGE(targettag,
									relation->rd_node.dbNode,
									relation->rd_id,
									blkno);

	targettaghash = PredicateLockTargetTagHashCode(&targettag);
	partitionLock = PredicateLockHashPartitionLock(targettaghash);
	LWLockAcquire(partitionLock, LW_SHARED);
	target = (PREDICATELOCKTARGET *)
		hash_search_with_hash_value(PredicateLockTargetHash,
									&targettag, targettaghash,
									HASH_FIND, NULL);
	LWLockRelease(partitionLock);

	return (target != NULL);
}