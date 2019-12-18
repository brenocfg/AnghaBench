#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int eas_used; int /*<<< orphan*/ * entryallocator; int /*<<< orphan*/  allocatedMemory; } ;
typedef  int /*<<< orphan*/  RBTNode ;
typedef  int /*<<< orphan*/  GinEntryAccumulator ;
typedef  TYPE_1__ BuildAccumulator ;

/* Variables and functions */
 int DEF_NENTRY ; 
 scalar_t__ GetMemoryChunkSpace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * palloc (int) ; 

__attribute__((used)) static RBTNode *
ginAllocEntryAccumulator(void *arg)
{
	BuildAccumulator *accum = (BuildAccumulator *) arg;
	GinEntryAccumulator *ea;

	/*
	 * Allocate memory by rather big chunks to decrease overhead.  We have no
	 * need to reclaim RBTNodes individually, so this costs nothing.
	 */
	if (accum->entryallocator == NULL || accum->eas_used >= DEF_NENTRY)
	{
		accum->entryallocator = palloc(sizeof(GinEntryAccumulator) * DEF_NENTRY);
		accum->allocatedMemory += GetMemoryChunkSpace(accum->entryallocator);
		accum->eas_used = 0;
	}

	/* Allocate new RBTNode from current chunk */
	ea = accum->entryallocator + accum->eas_used;
	accum->eas_used++;

	return (RBTNode *) ea;
}