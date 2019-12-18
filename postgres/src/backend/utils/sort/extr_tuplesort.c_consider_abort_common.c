#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; int memtupcount; int abbrevNext; TYPE_2__* sortKeys; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_5__ {int /*<<< orphan*/ * abbrev_full_comparator; int /*<<< orphan*/  (* abbrev_abort ) (int,TYPE_2__*) ;int /*<<< orphan*/ * abbrev_converter; int /*<<< orphan*/ * comparator; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ TSS_INITIAL ; 
 int /*<<< orphan*/  stub1 (int,TYPE_2__*) ; 

__attribute__((used)) static bool
consider_abort_common(Tuplesortstate *state)
{
	Assert(state->sortKeys[0].abbrev_converter != NULL);
	Assert(state->sortKeys[0].abbrev_abort != NULL);
	Assert(state->sortKeys[0].abbrev_full_comparator != NULL);

	/*
	 * Check effectiveness of abbreviation optimization.  Consider aborting
	 * when still within memory limit.
	 */
	if (state->status == TSS_INITIAL &&
		state->memtupcount >= state->abbrevNext)
	{
		state->abbrevNext *= 2;

		/*
		 * Check opclass-supplied abbreviation abort routine.  It may indicate
		 * that abbreviation should not proceed.
		 */
		if (!state->sortKeys->abbrev_abort(state->memtupcount,
										   state->sortKeys))
			return false;

		/*
		 * Finally, restore authoritative comparator, and indicate that
		 * abbreviation is not in play by setting abbrev_converter to NULL
		 */
		state->sortKeys[0].comparator = state->sortKeys[0].abbrev_full_comparator;
		state->sortKeys[0].abbrev_converter = NULL;
		/* Not strictly necessary, but be tidy */
		state->sortKeys[0].abbrev_abort = NULL;
		state->sortKeys[0].abbrev_full_comparator = NULL;

		/* Give up - expect original pass-by-value representation */
		return true;
	}

	return false;
}