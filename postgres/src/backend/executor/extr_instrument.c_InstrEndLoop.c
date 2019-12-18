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
struct TYPE_3__ {int running; double total; int nloops; scalar_t__ tuplecount; scalar_t__ firsttuple; int /*<<< orphan*/  counter; int /*<<< orphan*/  starttime; int /*<<< orphan*/  ntuples; int /*<<< orphan*/  startup; } ;
typedef  TYPE_1__ Instrumentation ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 double INSTR_TIME_GET_DOUBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_IS_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
InstrEndLoop(Instrumentation *instr)
{
	double		totaltime;

	/* Skip if nothing has happened, or already shut down */
	if (!instr->running)
		return;

	if (!INSTR_TIME_IS_ZERO(instr->starttime))
		elog(ERROR, "InstrEndLoop called on running node");

	/* Accumulate per-cycle statistics into totals */
	totaltime = INSTR_TIME_GET_DOUBLE(instr->counter);

	instr->startup += instr->firsttuple;
	instr->total += totaltime;
	instr->ntuples += instr->tuplecount;
	instr->nloops += 1;

	/* Reset for next cycle (if any) */
	instr->running = false;
	INSTR_TIME_SET_ZERO(instr->starttime);
	INSTR_TIME_SET_ZERO(instr->counter);
	instr->firsttuple = 0;
	instr->tuplecount = 0;
}