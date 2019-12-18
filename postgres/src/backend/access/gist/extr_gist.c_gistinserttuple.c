#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  int /*<<< orphan*/  GISTInsertState ;
typedef  int /*<<< orphan*/  GISTInsertStack ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBuffer ; 
 int gistinserttuples (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
gistinserttuple(GISTInsertState *state, GISTInsertStack *stack,
				GISTSTATE *giststate, IndexTuple tuple, OffsetNumber oldoffnum)
{
	return gistinserttuples(state, stack, giststate, &tuple, 1, oldoffnum,
							InvalidBuffer, InvalidBuffer, false, false);
}