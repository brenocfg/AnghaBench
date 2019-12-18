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
typedef  int /*<<< orphan*/  dsa_pointer_atomic ;
struct TYPE_9__ {int /*<<< orphan*/  area; TYPE_2__* parallel_state; TYPE_1__* batches; } ;
struct TYPE_8__ {int /*<<< orphan*/  buckets; } ;
struct TYPE_7__ {int nbuckets; } ;
struct TYPE_6__ {TYPE_3__* shared; } ;
typedef  TYPE_3__ ParallelHashJoinBatch ;
typedef  TYPE_4__* HashJoinTable ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidDsaPointer ; 
 int /*<<< orphan*/  dsa_allocate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_pointer_atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecParallelHashTableAlloc(HashJoinTable hashtable, int batchno)
{
	ParallelHashJoinBatch *batch = hashtable->batches[batchno].shared;
	dsa_pointer_atomic *buckets;
	int			nbuckets = hashtable->parallel_state->nbuckets;
	int			i;

	batch->buckets =
		dsa_allocate(hashtable->area, sizeof(dsa_pointer_atomic) * nbuckets);
	buckets = (dsa_pointer_atomic *)
		dsa_get_address(hashtable->area, batch->buckets);
	for (i = 0; i < nbuckets; ++i)
		dsa_pointer_atomic_init(&buckets[i], InvalidDsaPointer);
}