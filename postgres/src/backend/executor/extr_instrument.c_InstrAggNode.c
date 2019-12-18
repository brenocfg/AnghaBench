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
struct TYPE_4__ {int running; scalar_t__ firsttuple; int /*<<< orphan*/  bufusage; scalar_t__ need_bufusage; scalar_t__ nfiltered2; scalar_t__ nfiltered1; scalar_t__ nloops; scalar_t__ ntuples2; scalar_t__ ntuples; scalar_t__ total; scalar_t__ startup; scalar_t__ tuplecount; int /*<<< orphan*/  counter; } ;
typedef  TYPE_1__ Instrumentation ;

/* Variables and functions */
 int /*<<< orphan*/  BufferUsageAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSTR_TIME_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
InstrAggNode(Instrumentation *dst, Instrumentation *add)
{
	if (!dst->running && add->running)
	{
		dst->running = true;
		dst->firsttuple = add->firsttuple;
	}
	else if (dst->running && add->running && dst->firsttuple > add->firsttuple)
		dst->firsttuple = add->firsttuple;

	INSTR_TIME_ADD(dst->counter, add->counter);

	dst->tuplecount += add->tuplecount;
	dst->startup += add->startup;
	dst->total += add->total;
	dst->ntuples += add->ntuples;
	dst->ntuples2 += add->ntuples2;
	dst->nloops += add->nloops;
	dst->nfiltered1 += add->nfiltered1;
	dst->nfiltered2 += add->nfiltered2;

	/* Add delta of buffer usage since entry to node's totals */
	if (dst->need_bufusage)
		BufferUsageAdd(&dst->bufusage, &add->bufusage);
}