#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * myXact; TYPE_1__* myTarget; } ;
struct TYPE_9__ {TYPE_2__ tag; } ;
struct TYPE_8__ {int nelements; int /*<<< orphan*/ * xacts; int /*<<< orphan*/ * locktags; } ;
struct TYPE_6__ {int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  SERIALIZABLEXACT ;
typedef  TYPE_3__ PredicateLockData ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  TYPE_4__ PREDICATELOCK ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int NUM_PREDICATELOCK_PARTITIONS ; 
 int /*<<< orphan*/  PredicateLockHash ; 
 int /*<<< orphan*/  PredicateLockHashPartitionLockByIndex (int) ; 
 int /*<<< orphan*/  SerializableXactHashLock ; 
 int hash_get_num_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

PredicateLockData *
GetPredicateLockStatusData(void)
{
	PredicateLockData *data;
	int			i;
	int			els,
				el;
	HASH_SEQ_STATUS seqstat;
	PREDICATELOCK *predlock;

	data = (PredicateLockData *) palloc(sizeof(PredicateLockData));

	/*
	 * To ensure consistency, take simultaneous locks on all partition locks
	 * in ascending order, then SerializableXactHashLock.
	 */
	for (i = 0; i < NUM_PREDICATELOCK_PARTITIONS; i++)
		LWLockAcquire(PredicateLockHashPartitionLockByIndex(i), LW_SHARED);
	LWLockAcquire(SerializableXactHashLock, LW_SHARED);

	/* Get number of locks and allocate appropriately-sized arrays. */
	els = hash_get_num_entries(PredicateLockHash);
	data->nelements = els;
	data->locktags = (PREDICATELOCKTARGETTAG *)
		palloc(sizeof(PREDICATELOCKTARGETTAG) * els);
	data->xacts = (SERIALIZABLEXACT *)
		palloc(sizeof(SERIALIZABLEXACT) * els);


	/* Scan through PredicateLockHash and copy contents */
	hash_seq_init(&seqstat, PredicateLockHash);

	el = 0;

	while ((predlock = (PREDICATELOCK *) hash_seq_search(&seqstat)))
	{
		data->locktags[el] = predlock->tag.myTarget->tag;
		data->xacts[el] = *predlock->tag.myXact;
		el++;
	}

	Assert(el == els);

	/* Release locks in reverse order */
	LWLockRelease(SerializableXactHashLock);
	for (i = NUM_PREDICATELOCK_PARTITIONS - 1; i >= 0; i--)
		LWLockRelease(PredicateLockHashPartitionLockByIndex(i));

	return data;
}