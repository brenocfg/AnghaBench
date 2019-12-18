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
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
InstrInit(Instrumentation *instr, int instrument_options)
{
	memset(instr, 0, sizeof(Instrumentation));
	instr->need_bufusage = (instrument_options & INSTRUMENT_BUFFERS) != 0;
	instr->need_timer = (instrument_options & INSTRUMENT_TIMER) != 0;
}