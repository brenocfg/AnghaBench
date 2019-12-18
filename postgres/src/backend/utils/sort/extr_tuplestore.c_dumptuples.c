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
struct TYPE_5__ {int memtupdeleted; int readptrcount; int memtupcount; int /*<<< orphan*/ * memtuples; int /*<<< orphan*/  myfile; TYPE_2__* readptrs; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_6__ {int current; int /*<<< orphan*/  offset; int /*<<< orphan*/  file; int /*<<< orphan*/  eof_reached; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int /*<<< orphan*/  BufFileTell (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITETUP (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dumptuples(Tuplestorestate *state)
{
	int			i;

	for (i = state->memtupdeleted;; i++)
	{
		TSReadPointer *readptr = state->readptrs;
		int			j;

		for (j = 0; j < state->readptrcount; readptr++, j++)
		{
			if (i == readptr->current && !readptr->eof_reached)
				BufFileTell(state->myfile,
							&readptr->file, &readptr->offset);
		}
		if (i >= state->memtupcount)
			break;
		WRITETUP(state, state->memtuples[i]);
	}
	state->memtupdeleted = 0;
	state->memtupcount = 0;
}