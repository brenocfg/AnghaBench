#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int eflags; int interXact; int truncated; int allowedMem; int availMem; int memtupsize; int growmemtuples; void** memtuples; int readptrcount; int readptrsize; TYPE_2__* readptrs; scalar_t__ activeptr; scalar_t__ tuples; scalar_t__ memtupcount; scalar_t__ memtupdeleted; int /*<<< orphan*/  resowner; int /*<<< orphan*/  context; int /*<<< orphan*/ * myfile; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_6__ {int eflags; int eof_reached; scalar_t__ current; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int ALLOCSET_SEPARATE_THRESHOLD ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (void**) ; 
 int Max (int,int) ; 
 int /*<<< orphan*/  TSS_INMEM ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static Tuplestorestate *
tuplestore_begin_common(int eflags, bool interXact, int maxKBytes)
{
	Tuplestorestate *state;

	state = (Tuplestorestate *) palloc0(sizeof(Tuplestorestate));

	state->status = TSS_INMEM;
	state->eflags = eflags;
	state->interXact = interXact;
	state->truncated = false;
	state->allowedMem = maxKBytes * 1024L;
	state->availMem = state->allowedMem;
	state->myfile = NULL;
	state->context = CurrentMemoryContext;
	state->resowner = CurrentResourceOwner;

	state->memtupdeleted = 0;
	state->memtupcount = 0;
	state->tuples = 0;

	/*
	 * Initial size of array must be more than ALLOCSET_SEPARATE_THRESHOLD;
	 * see comments in grow_memtuples().
	 */
	state->memtupsize = Max(16384 / sizeof(void *),
							ALLOCSET_SEPARATE_THRESHOLD / sizeof(void *) + 1);

	state->growmemtuples = true;
	state->memtuples = (void **) palloc(state->memtupsize * sizeof(void *));

	USEMEM(state, GetMemoryChunkSpace(state->memtuples));

	state->activeptr = 0;
	state->readptrcount = 1;
	state->readptrsize = 8;		/* arbitrary */
	state->readptrs = (TSReadPointer *)
		palloc(state->readptrsize * sizeof(TSReadPointer));

	state->readptrs[0].eflags = eflags;
	state->readptrs[0].eof_reached = false;
	state->readptrs[0].current = 0;

	return state;
}