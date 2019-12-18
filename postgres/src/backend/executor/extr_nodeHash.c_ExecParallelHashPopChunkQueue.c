#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_10__ {int /*<<< orphan*/  area; TYPE_2__* parallel_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  shared; } ;
struct TYPE_9__ {TYPE_1__ next; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  chunk_work_queue; } ;
typedef  TYPE_2__ ParallelHashJoinState ;
typedef  TYPE_3__* HashMemoryChunk ;
typedef  TYPE_4__* HashJoinTable ;

/* Variables and functions */
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HashMemoryChunk
ExecParallelHashPopChunkQueue(HashJoinTable hashtable, dsa_pointer *shared)
{
	ParallelHashJoinState *pstate = hashtable->parallel_state;
	HashMemoryChunk chunk;

	LWLockAcquire(&pstate->lock, LW_EXCLUSIVE);
	if (DsaPointerIsValid(pstate->chunk_work_queue))
	{
		*shared = pstate->chunk_work_queue;
		chunk = (HashMemoryChunk)
			dsa_get_address(hashtable->area, *shared);
		pstate->chunk_work_queue = chunk->next.shared;
	}
	else
		chunk = NULL;
	LWLockRelease(&pstate->lock);

	return chunk;
}