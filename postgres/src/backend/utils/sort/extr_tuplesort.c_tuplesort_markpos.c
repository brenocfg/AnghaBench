#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; int /*<<< orphan*/  eof_reached; int /*<<< orphan*/  markpos_eof; int /*<<< orphan*/  markpos_offset; int /*<<< orphan*/  markpos_block; int /*<<< orphan*/  result_tape; int /*<<< orphan*/  tapeset; int /*<<< orphan*/  current; int /*<<< orphan*/  randomAccess; int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LogicalTapeTell (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
#define  TSS_SORTEDINMEM 129 
#define  TSS_SORTEDONTAPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
tuplesort_markpos(Tuplesortstate *state)
{
	MemoryContext oldcontext = MemoryContextSwitchTo(state->sortcontext);

	Assert(state->randomAccess);

	switch (state->status)
	{
		case TSS_SORTEDINMEM:
			state->markpos_offset = state->current;
			state->markpos_eof = state->eof_reached;
			break;
		case TSS_SORTEDONTAPE:
			LogicalTapeTell(state->tapeset,
							state->result_tape,
							&state->markpos_block,
							&state->markpos_offset);
			state->markpos_eof = state->eof_reached;
			break;
		default:
			elog(ERROR, "invalid tuplesort state");
			break;
	}

	MemoryContextSwitchTo(oldcontext);
}