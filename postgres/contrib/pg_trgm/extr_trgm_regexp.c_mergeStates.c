#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* parent; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ TrgmState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static void
mergeStates(TrgmState *state1, TrgmState *state2)
{
	Assert(state1 != state2);
	Assert(!state1->parent);
	Assert(!state2->parent);

	/* state1 absorbs state2's flags */
	state1->flags |= state2->flags;

	/* state2, and indirectly all its children, become children of state1 */
	state2->parent = state1;
}