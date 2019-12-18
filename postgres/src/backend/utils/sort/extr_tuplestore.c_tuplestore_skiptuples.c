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
typedef  scalar_t__ int64 ;
struct TYPE_5__ {size_t activeptr; int status; scalar_t__ memtupcount; scalar_t__ memtupdeleted; int /*<<< orphan*/  truncated; TYPE_2__* readptrs; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_6__ {int eflags; int eof_reached; scalar_t__ current; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int EXEC_FLAG_BACKWARD ; 
#define  TSS_INMEM 128 
 int /*<<< orphan*/  pfree (void*) ; 
 void* tuplestore_gettuple (TYPE_1__*,int,int*) ; 

bool
tuplestore_skiptuples(Tuplestorestate *state, int64 ntuples, bool forward)
{
	TSReadPointer *readptr = &state->readptrs[state->activeptr];

	Assert(forward || (readptr->eflags & EXEC_FLAG_BACKWARD));

	if (ntuples <= 0)
		return true;

	switch (state->status)
	{
		case TSS_INMEM:
			if (forward)
			{
				if (readptr->eof_reached)
					return false;
				if (state->memtupcount - readptr->current >= ntuples)
				{
					readptr->current += ntuples;
					return true;
				}
				readptr->current = state->memtupcount;
				readptr->eof_reached = true;
				return false;
			}
			else
			{
				if (readptr->eof_reached)
				{
					readptr->current = state->memtupcount;
					readptr->eof_reached = false;
					ntuples--;
				}
				if (readptr->current - state->memtupdeleted > ntuples)
				{
					readptr->current -= ntuples;
					return true;
				}
				Assert(!state->truncated);
				readptr->current = state->memtupdeleted;
				return false;
			}
			break;

		default:
			/* We don't currently try hard to optimize other cases */
			while (ntuples-- > 0)
			{
				void	   *tuple;
				bool		should_free;

				tuple = tuplestore_gettuple(state, forward, &should_free);

				if (tuple == NULL)
					return false;
				if (should_free)
					pfree(tuple);
				CHECK_FOR_INTERRUPTS();
			}
			return true;
	}
}