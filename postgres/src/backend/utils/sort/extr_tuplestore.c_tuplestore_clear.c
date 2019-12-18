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
struct TYPE_5__ {int memtupdeleted; int memtupcount; int truncated; int readptrcount; TYPE_2__* readptrs; scalar_t__ tuples; int /*<<< orphan*/  status; int /*<<< orphan*/ * memtuples; int /*<<< orphan*/ * myfile; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_6__ {int eof_reached; scalar_t__ current; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int /*<<< orphan*/  BufFileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSS_INMEM ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

void
tuplestore_clear(Tuplestorestate *state)
{
	int			i;
	TSReadPointer *readptr;

	if (state->myfile)
		BufFileClose(state->myfile);
	state->myfile = NULL;
	if (state->memtuples)
	{
		for (i = state->memtupdeleted; i < state->memtupcount; i++)
		{
			FREEMEM(state, GetMemoryChunkSpace(state->memtuples[i]));
			pfree(state->memtuples[i]);
		}
	}
	state->status = TSS_INMEM;
	state->truncated = false;
	state->memtupdeleted = 0;
	state->memtupcount = 0;
	state->tuples = 0;
	readptr = state->readptrs;
	for (i = 0; i < state->readptrcount; readptr++, i++)
	{
		readptr->eof_reached = false;
		readptr->current = 0;
	}
}