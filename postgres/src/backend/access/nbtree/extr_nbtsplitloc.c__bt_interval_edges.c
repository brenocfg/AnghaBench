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
struct TYPE_7__ {scalar_t__ newitemoff; TYPE_1__* splits; int /*<<< orphan*/  nsplits; int /*<<< orphan*/  interval; } ;
struct TYPE_6__ {scalar_t__ firstoldonright; scalar_t__ newitemonleft; } ;
typedef  TYPE_1__ SplitPoint ;
typedef  TYPE_2__ FindSplitData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_bt_interval_edges(FindSplitData *state, SplitPoint **leftinterval,
				   SplitPoint **rightinterval)
{
	int			highsplit = Min(state->interval, state->nsplits);
	SplitPoint *deltaoptimal;

	deltaoptimal = state->splits;
	*leftinterval = NULL;
	*rightinterval = NULL;

	/*
	 * Delta is an absolute distance to optimal split point, so both the
	 * leftmost and rightmost split point will usually be at the end of the
	 * array
	 */
	for (int i = highsplit - 1; i >= 0; i--)
	{
		SplitPoint *distant = state->splits + i;

		if (distant->firstoldonright < deltaoptimal->firstoldonright)
		{
			if (*leftinterval == NULL)
				*leftinterval = distant;
		}
		else if (distant->firstoldonright > deltaoptimal->firstoldonright)
		{
			if (*rightinterval == NULL)
				*rightinterval = distant;
		}
		else if (!distant->newitemonleft && deltaoptimal->newitemonleft)
		{
			/*
			 * "incoming tuple will become first on right page" (distant) is
			 * to the left of "incoming tuple will become last on left page"
			 * (delta-optimal)
			 */
			Assert(distant->firstoldonright == state->newitemoff);
			if (*leftinterval == NULL)
				*leftinterval = distant;
		}
		else if (distant->newitemonleft && !deltaoptimal->newitemonleft)
		{
			/*
			 * "incoming tuple will become last on left page" (distant) is to
			 * the right of "incoming tuple will become first on right page"
			 * (delta-optimal)
			 */
			Assert(distant->firstoldonright == state->newitemoff);
			if (*rightinterval == NULL)
				*rightinterval = distant;
		}
		else
		{
			/* There was only one or two splits in initial split interval */
			Assert(distant == deltaoptimal);
			if (*leftinterval == NULL)
				*leftinterval = distant;
			if (*rightinterval == NULL)
				*rightinterval = distant;
		}

		if (*leftinterval && *rightinterval)
			return;
	}

	Assert(false);
}