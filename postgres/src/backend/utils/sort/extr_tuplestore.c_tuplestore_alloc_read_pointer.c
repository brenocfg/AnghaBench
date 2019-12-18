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
struct TYPE_5__ {scalar_t__ status; scalar_t__ memtupcount; int eflags; size_t readptrcount; size_t readptrsize; TYPE_2__* readptrs; } ;
typedef  TYPE_1__ Tuplestorestate ;
struct TYPE_6__ {int eflags; } ;
typedef  TYPE_2__ TSReadPointer ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TSS_INMEM ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ repalloc (TYPE_2__*,int) ; 

int
tuplestore_alloc_read_pointer(Tuplestorestate *state, int eflags)
{
	/* Check for possible increase of requirements */
	if (state->status != TSS_INMEM || state->memtupcount != 0)
	{
		if ((state->eflags | eflags) != state->eflags)
			elog(ERROR, "too late to require new tuplestore eflags");
	}

	/* Make room for another read pointer if needed */
	if (state->readptrcount >= state->readptrsize)
	{
		int			newcnt = state->readptrsize * 2;

		state->readptrs = (TSReadPointer *)
			repalloc(state->readptrs, newcnt * sizeof(TSReadPointer));
		state->readptrsize = newcnt;
	}

	/* And set it up */
	state->readptrs[state->readptrcount] = state->readptrs[0];
	state->readptrs[state->readptrcount].eflags = eflags;

	state->eflags |= eflags;

	return state->readptrcount++;
}