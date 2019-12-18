#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ lxid; } ;
struct TYPE_4__ {scalar_t__ lxid; int /*<<< orphan*/  relid; } ;
typedef  TYPE_1__* SeqTable ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ LocalTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  TopTransactionResourceOwner ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Relation
lock_and_open_sequence(SeqTable seq)
{
	LocalTransactionId thislxid = MyProc->lxid;

	/* Get the lock if not already held in this xact */
	if (seq->lxid != thislxid)
	{
		ResourceOwner currentOwner;

		currentOwner = CurrentResourceOwner;
		CurrentResourceOwner = TopTransactionResourceOwner;

		LockRelationOid(seq->relid, RowExclusiveLock);

		CurrentResourceOwner = currentOwner;

		/* Flag that we have a lock in the current xact */
		seq->lxid = thislxid;
	}

	/* We now know we have the lock, and can safely open the rel */
	return relation_open(seq->relid, NoLock);
}