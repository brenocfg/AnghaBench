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
struct TYPE_7__ {scalar_t__ newitemoff; TYPE_1__* splits; int /*<<< orphan*/  is_rightmost; int /*<<< orphan*/  nsplits; int /*<<< orphan*/  interval; } ;
struct TYPE_6__ {int newitemonleft; scalar_t__ firstoldonright; } ;
typedef  TYPE_1__ SplitPoint ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ FindSplitStrat ;
typedef  TYPE_2__ FindSplitData ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ MAX_LEAF_INTERVAL ; 
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SPLIT_MANY_DUPLICATES ; 
 int _bt_split_penalty (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static OffsetNumber
_bt_bestsplitloc(FindSplitData *state, int perfectpenalty,
				 bool *newitemonleft, FindSplitStrat strategy)
{
	int			bestpenalty,
				lowsplit;
	int			highsplit = Min(state->interval, state->nsplits);
	SplitPoint *final;

	bestpenalty = INT_MAX;
	lowsplit = 0;
	for (int i = lowsplit; i < highsplit; i++)
	{
		int			penalty;

		penalty = _bt_split_penalty(state, state->splits + i);

		if (penalty <= perfectpenalty)
		{
			bestpenalty = penalty;
			lowsplit = i;
			break;
		}

		if (penalty < bestpenalty)
		{
			bestpenalty = penalty;
			lowsplit = i;
		}
	}

	final = &state->splits[lowsplit];

	/*
	 * There is a risk that the "many duplicates" strategy will repeatedly do
	 * the wrong thing when there are monotonically decreasing insertions to
	 * the right of a large group of duplicates.   Repeated splits could leave
	 * a succession of right half pages with free space that can never be
	 * used.  This must be avoided.
	 *
	 * Consider the example of the leftmost page in a single integer attribute
	 * NULLS FIRST index which is almost filled with NULLs.  Monotonically
	 * decreasing integer insertions might cause the same leftmost page to
	 * split repeatedly at the same point.  Each split derives its new high
	 * key from the lowest current value to the immediate right of the large
	 * group of NULLs, which will always be higher than all future integer
	 * insertions, directing all future integer insertions to the same
	 * leftmost page.
	 */
	if (strategy == SPLIT_MANY_DUPLICATES && !state->is_rightmost &&
		!final->newitemonleft && final->firstoldonright >= state->newitemoff &&
		final->firstoldonright < state->newitemoff + MAX_LEAF_INTERVAL)
	{
		/*
		 * Avoid the problem by performing a 50:50 split when the new item is
		 * just to the right of the would-be "many duplicates" split point.
		 */
		final = &state->splits[0];
	}

	*newitemonleft = final->newitemonleft;
	return final->firstoldonright;
}