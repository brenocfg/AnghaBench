#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int indtuples; int /*<<< orphan*/  tmpCtx; int /*<<< orphan*/  spgstate; } ;
typedef  TYPE_1__ SpGistBuildState ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spgdoinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spgistBuildCallback(Relation index, ItemPointer tid, Datum *values,
					bool *isnull, bool tupleIsAlive, void *state)
{
	SpGistBuildState *buildstate = (SpGistBuildState *) state;
	MemoryContext oldCtx;

	/* Work in temp context, and reset it after each tuple */
	oldCtx = MemoryContextSwitchTo(buildstate->tmpCtx);

	/*
	 * Even though no concurrent insertions can be happening, we still might
	 * get a buffer-locking failure due to bgwriter or checkpointer taking a
	 * lock on some buffer.  So we need to be willing to retry.  We can flush
	 * any temp data when retrying.
	 */
	while (!spgdoinsert(index, &buildstate->spgstate, tid,
						*values, *isnull))
	{
		MemoryContextReset(buildstate->tmpCtx);
	}

	/* Update total tuple count */
	buildstate->indtuples += 1;

	MemoryContextSwitchTo(oldCtx);
	MemoryContextReset(buildstate->tmpCtx);
}