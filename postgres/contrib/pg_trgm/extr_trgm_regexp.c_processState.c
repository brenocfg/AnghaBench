#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TrgmStateKey ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  stateKey; } ;
typedef  TYPE_1__ TrgmState ;
struct TYPE_10__ {scalar_t__ keysQueue; } ;
typedef  TYPE_2__ TrgmNFA ;

/* Variables and functions */
 scalar_t__ NIL ; 
 int TSTATE_FIN ; 
 int /*<<< orphan*/  addArcs (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  addKey (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 

__attribute__((used)) static void
processState(TrgmNFA *trgmNFA, TrgmState *state)
{
	/* keysQueue should be NIL already, but make sure */
	trgmNFA->keysQueue = NIL;

	/*
	 * Add state's own key, and then process all keys added to keysQueue until
	 * queue is empty.  But we can quit if the state gets marked final.
	 */
	addKey(trgmNFA, state, &state->stateKey);
	while (trgmNFA->keysQueue != NIL && !(state->flags & TSTATE_FIN))
	{
		TrgmStateKey *key = (TrgmStateKey *) linitial(trgmNFA->keysQueue);

		trgmNFA->keysQueue = list_delete_first(trgmNFA->keysQueue);
		addKey(trgmNFA, state, key);
	}

	/*
	 * Add outgoing arcs only if state isn't final (we have no interest in
	 * outgoing arcs if we already match)
	 */
	if (!(state->flags & TSTATE_FIN))
		addArcs(trgmNFA, state);
}