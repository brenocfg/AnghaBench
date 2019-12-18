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
struct TYPE_3__ {int status; int eof_reached; int markpos_eof; long markpos_block; int /*<<< orphan*/  markpos_offset; int /*<<< orphan*/  result_tape; int /*<<< orphan*/  tapeset; int /*<<< orphan*/  current; int /*<<< orphan*/  randomAccess; int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LogicalTapeRewindForRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
#define  TSS_SORTEDINMEM 129 
#define  TSS_SORTEDONTAPE 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
tuplesort_rescan(Tuplesortstate *state)
{
	MemoryContext oldcontext = MemoryContextSwitchTo(state->sortcontext);

	Assert(state->randomAccess);

	switch (state->status)
	{
		case TSS_SORTEDINMEM:
			state->current = 0;
			state->eof_reached = false;
			state->markpos_offset = 0;
			state->markpos_eof = false;
			break;
		case TSS_SORTEDONTAPE:
			LogicalTapeRewindForRead(state->tapeset,
									 state->result_tape,
									 0);
			state->eof_reached = false;
			state->markpos_block = 0L;
			state->markpos_offset = 0;
			state->markpos_eof = false;
			break;
		default:
			elog(ERROR, "invalid tuplesort state");
			break;
	}

	MemoryContextSwitchTo(oldcontext);
}