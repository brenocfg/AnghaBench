#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer_atomic ;
struct TYPE_7__ {int /*<<< orphan*/ * shared; } ;
struct TYPE_11__ {int curbatch; TYPE_4__* batches; scalar_t__ current_chunk_shared; int /*<<< orphan*/ * current_chunk; int /*<<< orphan*/  nbuckets; int /*<<< orphan*/  log2_nbuckets; TYPE_3__* parallel_state; int /*<<< orphan*/  area; TYPE_1__ buckets; } ;
struct TYPE_10__ {int at_least_one_chunk; TYPE_2__* shared; } ;
struct TYPE_9__ {int /*<<< orphan*/  nbuckets; } ;
struct TYPE_8__ {scalar_t__ buckets; } ;
typedef  TYPE_5__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidDsaPointer ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  my_log2 (int /*<<< orphan*/ ) ; 

void
ExecParallelHashTableSetCurrentBatch(HashJoinTable hashtable, int batchno)
{
	Assert(hashtable->batches[batchno].shared->buckets != InvalidDsaPointer);

	hashtable->curbatch = batchno;
	hashtable->buckets.shared = (dsa_pointer_atomic *)
		dsa_get_address(hashtable->area,
						hashtable->batches[batchno].shared->buckets);
	hashtable->nbuckets = hashtable->parallel_state->nbuckets;
	hashtable->log2_nbuckets = my_log2(hashtable->nbuckets);
	hashtable->current_chunk = NULL;
	hashtable->current_chunk_shared = InvalidDsaPointer;
	hashtable->batches[batchno].at_least_one_chunk = false;
}