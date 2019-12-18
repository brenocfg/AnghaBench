#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_7__ {scalar_t__ status; scalar_t__ memtupcount; int bounded; int bound; TYPE_1__* sortKeys; } ;
typedef  TYPE_2__ Tuplesortstate ;
struct TYPE_6__ {int /*<<< orphan*/ * abbrev_full_comparator; int /*<<< orphan*/ * abbrev_abort; int /*<<< orphan*/ * comparator; int /*<<< orphan*/ * abbrev_converter; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int INT_MAX ; 
 scalar_t__ LEADER (TYPE_2__*) ; 
 scalar_t__ TSS_INITIAL ; 
 int /*<<< orphan*/  WORKER (TYPE_2__*) ; 
 int /*<<< orphan*/  optimize_bounded_sort ; 

void
tuplesort_set_bound(Tuplesortstate *state, int64 bound)
{
	/* Assert we're called before loading any tuples */
	Assert(state->status == TSS_INITIAL && state->memtupcount == 0);
	/* Can't set the bound twice, either */
	Assert(!state->bounded);
	/* Also, this shouldn't be called in a parallel worker */
	Assert(!WORKER(state));

	/* Parallel leader allows but ignores hint */
	if (LEADER(state))
		return;

#ifdef DEBUG_BOUNDED_SORT
	/* Honor GUC setting that disables the feature (for easy testing) */
	if (!optimize_bounded_sort)
		return;
#endif

	/* We want to be able to compute bound * 2, so limit the setting */
	if (bound > (int64) (INT_MAX / 2))
		return;

	state->bounded = true;
	state->bound = (int) bound;

	/*
	 * Bounded sorts are not an effective target for abbreviated key
	 * optimization.  Disable by setting state to be consistent with no
	 * abbreviation support.
	 */
	state->sortKeys->abbrev_converter = NULL;
	if (state->sortKeys->abbrev_full_comparator)
		state->sortKeys->comparator = state->sortKeys->abbrev_full_comparator;

	/* Not strictly necessary, but be tidy */
	state->sortKeys->abbrev_abort = NULL;
	state->sortKeys->abbrev_full_comparator = NULL;
}