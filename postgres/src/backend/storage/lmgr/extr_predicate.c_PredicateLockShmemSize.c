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
typedef  int Size ;
typedef  int /*<<< orphan*/  SHM_QUEUE ;
typedef  int /*<<< orphan*/  SERIALIZABLEXID ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGET ;
typedef  int /*<<< orphan*/  PREDICATELOCK ;
typedef  int /*<<< orphan*/  OldSerXidControlData ;

/* Variables and functions */
 long MaxBackends ; 
 long NPREDICATELOCKTARGETENTS () ; 
 int /*<<< orphan*/  NUM_OLDSERXID_BUFFERS ; 
 int PredXactListDataSize ; 
 int /*<<< orphan*/  PredXactListElementDataSize ; 
 int /*<<< orphan*/  RWConflictDataSize ; 
 int RWConflictPoolHeaderDataSize ; 
 int SimpleLruShmemSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int add_size (int,int) ; 
 int hash_estimate_size (long,int) ; 
 long max_prepared_xacts ; 
 int mul_size (int,int /*<<< orphan*/ ) ; 

Size
PredicateLockShmemSize(void)
{
	Size		size = 0;
	long		max_table_size;

	/* predicate lock target hash table */
	max_table_size = NPREDICATELOCKTARGETENTS();
	size = add_size(size, hash_estimate_size(max_table_size,
											 sizeof(PREDICATELOCKTARGET)));

	/* predicate lock hash table */
	max_table_size *= 2;
	size = add_size(size, hash_estimate_size(max_table_size,
											 sizeof(PREDICATELOCK)));

	/*
	 * Since NPREDICATELOCKTARGETENTS is only an estimate, add 10% safety
	 * margin.
	 */
	size = add_size(size, size / 10);

	/* transaction list */
	max_table_size = MaxBackends + max_prepared_xacts;
	max_table_size *= 10;
	size = add_size(size, PredXactListDataSize);
	size = add_size(size, mul_size((Size) max_table_size,
								   PredXactListElementDataSize));

	/* transaction xid table */
	size = add_size(size, hash_estimate_size(max_table_size,
											 sizeof(SERIALIZABLEXID)));

	/* rw-conflict pool */
	max_table_size *= 5;
	size = add_size(size, RWConflictPoolHeaderDataSize);
	size = add_size(size, mul_size((Size) max_table_size,
								   RWConflictDataSize));

	/* Head for list of finished serializable transactions. */
	size = add_size(size, sizeof(SHM_QUEUE));

	/* Shared memory structures for SLRU tracking of old committed xids. */
	size = add_size(size, sizeof(OldSerXidControlData));
	size = add_size(size, SimpleLruShmemSize(NUM_OLDSERXID_BUFFERS, 0));

	return size;
}