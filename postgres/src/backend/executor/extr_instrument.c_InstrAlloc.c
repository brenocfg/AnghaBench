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
struct TYPE_4__ {int need_bufusage; int need_timer; } ;
typedef  TYPE_1__ Instrumentation ;

/* Variables and functions */
 int INSTRUMENT_BUFFERS ; 
 int INSTRUMENT_TIMER ; 
 TYPE_1__* palloc0 (int) ; 

Instrumentation *
InstrAlloc(int n, int instrument_options)
{
	Instrumentation *instr;

	/* initialize all fields to zeroes, then modify as needed */
	instr = palloc0(n * sizeof(Instrumentation));
	if (instrument_options & (INSTRUMENT_BUFFERS | INSTRUMENT_TIMER))
	{
		bool		need_buffers = (instrument_options & INSTRUMENT_BUFFERS) != 0;
		bool		need_timer = (instrument_options & INSTRUMENT_TIMER) != 0;
		int			i;

		for (i = 0; i < n; i++)
		{
			instr[i].need_bufusage = need_buffers;
			instr[i].need_timer = need_timer;
		}
	}

	return instr;
}