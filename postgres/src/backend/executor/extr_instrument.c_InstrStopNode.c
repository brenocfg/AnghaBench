#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_3__ {double tuplecount; int running; int /*<<< orphan*/  counter; int /*<<< orphan*/  firsttuple; int /*<<< orphan*/  bufusage_start; int /*<<< orphan*/  bufusage; scalar_t__ need_bufusage; int /*<<< orphan*/  starttime; scalar_t__ need_timer; } ;
typedef  TYPE_1__ Instrumentation ;

/* Variables and functions */
 int /*<<< orphan*/  BufferUsageAccumDiff (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INSTR_TIME_ACCUM_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_GET_DOUBLE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSTR_TIME_IS_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pgBufferUsage ; 

void
InstrStopNode(Instrumentation *instr, double nTuples)
{
	instr_time	endtime;

	/* count the returned tuples */
	instr->tuplecount += nTuples;

	/* let's update the time only if the timer was requested */
	if (instr->need_timer)
	{
		if (INSTR_TIME_IS_ZERO(instr->starttime))
			elog(ERROR, "InstrStopNode called without start");

		INSTR_TIME_SET_CURRENT(endtime);
		INSTR_TIME_ACCUM_DIFF(instr->counter, endtime, instr->starttime);

		INSTR_TIME_SET_ZERO(instr->starttime);
	}

	/* Add delta of buffer usage since entry to node's totals */
	if (instr->need_bufusage)
		BufferUsageAccumDiff(&instr->bufusage,
							 &pgBufferUsage, &instr->bufusage_start);

	/* Is this the first tuple of this cycle? */
	if (!instr->running)
	{
		instr->running = true;
		instr->firsttuple = INSTR_TIME_GET_DOUBLE(instr->counter);
	}
}