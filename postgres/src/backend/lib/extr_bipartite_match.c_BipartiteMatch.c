#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int u_size; int v_size; short** adjacency; short* pair_uv; short* pair_vu; short* distance; short* queue; scalar_t__ matching; } ;
typedef  TYPE_1__ BipartiteMatchState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int SHRT_MAX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hk_breadth_search (TYPE_1__*) ; 
 scalar_t__ hk_depth_search (TYPE_1__*,int) ; 
 TYPE_1__* palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

BipartiteMatchState *
BipartiteMatch(int u_size, int v_size, short **adjacency)
{
	BipartiteMatchState *state = palloc(sizeof(BipartiteMatchState));

	if (u_size < 0 || u_size >= SHRT_MAX ||
		v_size < 0 || v_size >= SHRT_MAX)
		elog(ERROR, "invalid set size for BipartiteMatch");

	state->u_size = u_size;
	state->v_size = v_size;
	state->adjacency = adjacency;
	state->matching = 0;
	state->pair_uv = (short *) palloc0((u_size + 1) * sizeof(short));
	state->pair_vu = (short *) palloc0((v_size + 1) * sizeof(short));
	state->distance = (short *) palloc((u_size + 1) * sizeof(short));
	state->queue = (short *) palloc((u_size + 2) * sizeof(short));

	while (hk_breadth_search(state))
	{
		int			u;

		for (u = 1; u <= u_size; u++)
		{
			if (state->pair_uv[u] == 0)
				if (hk_depth_search(state, u))
					state->matching++;
		}

		CHECK_FOR_INTERRUPTS(); /* just in case */
	}

	return state;
}