#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* result; } ;
struct TYPE_7__ {int nEvents; struct TYPE_7__* events; int /*<<< orphan*/ * errFields; int /*<<< orphan*/ * paramDescs; struct TYPE_7__* tuples; int /*<<< orphan*/ * attDescs; struct TYPE_7__* next; struct TYPE_7__* curBlock; struct TYPE_7__* name; int /*<<< orphan*/  passThrough; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;scalar_t__ resultInitialized; } ;
typedef  TYPE_1__ PGresult_data ;
typedef  TYPE_1__ PGresult ;
typedef  TYPE_3__ PGEventResultDestroy ;

/* Variables and functions */
 int /*<<< orphan*/  PGEVT_RESULTDESTROY ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

void
PQclear(PGresult *res)
{
	PGresult_data *block;
	int			i;

	if (!res)
		return;

	for (i = 0; i < res->nEvents; i++)
	{
		/* only send DESTROY to successfully-initialized event procs */
		if (res->events[i].resultInitialized)
		{
			PGEventResultDestroy evt;

			evt.result = res;
			(void) res->events[i].proc(PGEVT_RESULTDESTROY, &evt,
									   res->events[i].passThrough);
		}
		free(res->events[i].name);
	}

	if (res->events)
		free(res->events);

	/* Free all the subsidiary blocks */
	while ((block = res->curBlock) != NULL)
	{
		res->curBlock = block->next;
		free(block);
	}

	/* Free the top-level tuple pointer array */
	if (res->tuples)
		free(res->tuples);

	/* zero out the pointer fields to catch programming errors */
	res->attDescs = NULL;
	res->tuples = NULL;
	res->paramDescs = NULL;
	res->errFields = NULL;
	res->events = NULL;
	res->nEvents = 0;
	/* res->curBlock was zeroed out earlier */

	/* Free the PGresult structure itself */
	free(res);
}