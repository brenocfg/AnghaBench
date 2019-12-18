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
typedef  int /*<<< orphan*/  TrgmStateKey ;
struct TYPE_6__ {int /*<<< orphan*/ * tentParent; scalar_t__ tentFlags; int /*<<< orphan*/ * parent; int /*<<< orphan*/  snumber; scalar_t__ flags; void* enterKeys; void* arcs; } ;
typedef  TYPE_1__ TrgmState ;
struct TYPE_7__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  nstates; int /*<<< orphan*/  states; } ;
typedef  TYPE_2__ TrgmNFA ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 void* NIL ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static TrgmState *
getState(TrgmNFA *trgmNFA, TrgmStateKey *key)
{
	TrgmState  *state;
	bool		found;

	state = (TrgmState *) hash_search(trgmNFA->states, key, HASH_ENTER,
									  &found);
	if (!found)
	{
		/* New state: initialize and queue it */
		state->arcs = NIL;
		state->enterKeys = NIL;
		state->flags = 0;
		/* states are initially given negative numbers */
		state->snumber = -(++trgmNFA->nstates);
		state->parent = NULL;
		state->tentFlags = 0;
		state->tentParent = NULL;

		trgmNFA->queue = lappend(trgmNFA->queue, state);
	}
	return state;
}