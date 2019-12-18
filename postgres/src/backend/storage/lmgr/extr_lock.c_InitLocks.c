#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {int keysize; int entrysize; void* num_partitions; int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  PROCLOCKTAG ;
typedef  int /*<<< orphan*/  PROCLOCK ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  LOCK ;
typedef  int /*<<< orphan*/  LOCALLOCKTAG ;
typedef  int /*<<< orphan*/  LOCALLOCK ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  FastPathStrongRelationLockData ;

/* Variables and functions */
 TYPE_3__* FastPathStrongRelationLocks ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int HASH_FUNCTION ; 
 int HASH_PARTITION ; 
 scalar_t__ LockMethodLocalHash ; 
 void* LockMethodLockHash ; 
 void* LockMethodProcLockHash ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 long NLOCKENTS () ; 
 void* NUM_LOCK_PARTITIONS ; 
 void* ShmemInitHash (char*,long,long,TYPE_1__*,int) ; 
 TYPE_3__* ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 scalar_t__ hash_create (char*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  hash_destroy (scalar_t__) ; 
 int /*<<< orphan*/  proclock_hash ; 

void
InitLocks(void)
{
	HASHCTL		info;
	long		init_table_size,
				max_table_size;
	bool		found;

	/*
	 * Compute init/max size to request for lock hashtables.  Note these
	 * calculations must agree with LockShmemSize!
	 */
	max_table_size = NLOCKENTS();
	init_table_size = max_table_size / 2;

	/*
	 * Allocate hash table for LOCK structs.  This stores per-locked-object
	 * information.
	 */
	MemSet(&info, 0, sizeof(info));
	info.keysize = sizeof(LOCKTAG);
	info.entrysize = sizeof(LOCK);
	info.num_partitions = NUM_LOCK_PARTITIONS;

	LockMethodLockHash = ShmemInitHash("LOCK hash",
									   init_table_size,
									   max_table_size,
									   &info,
									   HASH_ELEM | HASH_BLOBS | HASH_PARTITION);

	/* Assume an average of 2 holders per lock */
	max_table_size *= 2;
	init_table_size *= 2;

	/*
	 * Allocate hash table for PROCLOCK structs.  This stores
	 * per-lock-per-holder information.
	 */
	info.keysize = sizeof(PROCLOCKTAG);
	info.entrysize = sizeof(PROCLOCK);
	info.hash = proclock_hash;
	info.num_partitions = NUM_LOCK_PARTITIONS;

	LockMethodProcLockHash = ShmemInitHash("PROCLOCK hash",
										   init_table_size,
										   max_table_size,
										   &info,
										   HASH_ELEM | HASH_FUNCTION | HASH_PARTITION);

	/*
	 * Allocate fast-path structures.
	 */
	FastPathStrongRelationLocks =
		ShmemInitStruct("Fast Path Strong Relation Lock Data",
						sizeof(FastPathStrongRelationLockData), &found);
	if (!found)
		SpinLockInit(&FastPathStrongRelationLocks->mutex);

	/*
	 * Allocate non-shared hash table for LOCALLOCK structs.  This stores lock
	 * counts and resource owner information.
	 *
	 * The non-shared table could already exist in this process (this occurs
	 * when the postmaster is recreating shared memory after a backend crash).
	 * If so, delete and recreate it.  (We could simply leave it, since it
	 * ought to be empty in the postmaster, but for safety let's zap it.)
	 */
	if (LockMethodLocalHash)
		hash_destroy(LockMethodLocalHash);

	info.keysize = sizeof(LOCALLOCKTAG);
	info.entrysize = sizeof(LOCALLOCK);

	LockMethodLocalHash = hash_create("LOCALLOCK hash",
									  16,
									  &info,
									  HASH_ELEM | HASH_BLOBS);
}