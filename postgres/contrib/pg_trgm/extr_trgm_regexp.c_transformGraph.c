#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  initkey ;
struct TYPE_14__ {void** colors; } ;
struct TYPE_15__ {int /*<<< orphan*/  nstate; TYPE_1__ prefix; } ;
typedef  TYPE_2__ TrgmStateKey ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ TrgmState ;
struct TYPE_17__ {scalar_t__ queue; scalar_t__ arcsCount; int overflowed; int /*<<< orphan*/  states; TYPE_3__* initState; int /*<<< orphan*/  regex; scalar_t__ nstates; scalar_t__ keysQueue; } ;
typedef  TYPE_4__ TrgmNFA ;
struct TYPE_18__ {int keysize; int entrysize; int /*<<< orphan*/  hcxt; } ;
typedef  TYPE_5__ HASHCTL ;

/* Variables and functions */
 void* COLOR_UNKNOWN ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 scalar_t__ MAX_EXPANDED_ARCS ; 
 scalar_t__ MAX_EXPANDED_STATES ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  TSTATE_FIN ; 
 int /*<<< orphan*/  TSTATE_INIT ; 
 TYPE_3__* getState (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  hash_create (char*,int,TYPE_5__*,int) ; 
 scalar_t__ hash_get_num_entries (int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 int /*<<< orphan*/  pg_reg_getinitialstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processState (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void
transformGraph(TrgmNFA *trgmNFA)
{
	HASHCTL		hashCtl;
	TrgmStateKey initkey;
	TrgmState  *initstate;

	/* Initialize this stage's workspace in trgmNFA struct */
	trgmNFA->queue = NIL;
	trgmNFA->keysQueue = NIL;
	trgmNFA->arcsCount = 0;
	trgmNFA->overflowed = false;

	/* Create hashtable for states */
	hashCtl.keysize = sizeof(TrgmStateKey);
	hashCtl.entrysize = sizeof(TrgmState);
	hashCtl.hcxt = CurrentMemoryContext;
	trgmNFA->states = hash_create("Trigram NFA",
								  1024,
								  &hashCtl,
								  HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
	trgmNFA->nstates = 0;

	/* Create initial state: ambiguous prefix, NFA's initial state */
	MemSet(&initkey, 0, sizeof(initkey));
	initkey.prefix.colors[0] = COLOR_UNKNOWN;
	initkey.prefix.colors[1] = COLOR_UNKNOWN;
	initkey.nstate = pg_reg_getinitialstate(trgmNFA->regex);

	initstate = getState(trgmNFA, &initkey);
	initstate->flags |= TSTATE_INIT;
	trgmNFA->initState = initstate;

	/*
	 * Recursively build the expanded graph by processing queue of states
	 * (breadth-first search).  getState already put initstate in the queue.
	 */
	while (trgmNFA->queue != NIL)
	{
		TrgmState  *state = (TrgmState *) linitial(trgmNFA->queue);

		trgmNFA->queue = list_delete_first(trgmNFA->queue);

		/*
		 * If we overflowed then just mark state as final.  Otherwise do
		 * actual processing.
		 */
		if (trgmNFA->overflowed)
			state->flags |= TSTATE_FIN;
		else
			processState(trgmNFA, state);

		/* Did we overflow? */
		if (trgmNFA->arcsCount > MAX_EXPANDED_ARCS ||
			hash_get_num_entries(trgmNFA->states) > MAX_EXPANDED_STATES)
			trgmNFA->overflowed = true;
	}
}