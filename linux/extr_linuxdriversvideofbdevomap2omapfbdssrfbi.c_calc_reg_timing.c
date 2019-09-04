#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rfbi_timings {int clk_div; void* cs_pulse_width; void* access_time; void* we_cycle_time; void* re_cycle_time; void* we_off_time; void* we_on_time; void* re_off_time; void* re_on_time; void* cs_off_time; void* cs_on_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*,void*,void*,...) ; 
 int rfbi_convert_timings (struct rfbi_timings*) ; 
 void* round_to_extif_ticks (void*,int) ; 

__attribute__((used)) static int calc_reg_timing(struct rfbi_timings *t, int div)
{
	t->clk_div = div;

	t->cs_on_time = round_to_extif_ticks(t->cs_on_time, div);

	t->we_on_time = round_to_extif_ticks(t->we_on_time, div);
	t->we_off_time = round_to_extif_ticks(t->we_off_time, div);
	t->we_cycle_time = round_to_extif_ticks(t->we_cycle_time, div);

	t->re_on_time = round_to_extif_ticks(t->re_on_time, div);
	t->re_off_time = round_to_extif_ticks(t->re_off_time, div);
	t->re_cycle_time = round_to_extif_ticks(t->re_cycle_time, div);

	t->access_time = round_to_extif_ticks(t->access_time, div);
	t->cs_off_time = round_to_extif_ticks(t->cs_off_time, div);
	t->cs_pulse_width = round_to_extif_ticks(t->cs_pulse_width, div);

	DSSDBG("[reg]cson %d csoff %d reon %d reoff %d\n",
	       t->cs_on_time, t->cs_off_time, t->re_on_time, t->re_off_time);
	DSSDBG("[reg]weon %d weoff %d recyc %d wecyc %d\n",
	       t->we_on_time, t->we_off_time, t->re_cycle_time,
	       t->we_cycle_time);
	DSSDBG("[reg]rdaccess %d cspulse %d\n",
	       t->access_time, t->cs_pulse_width);

	return rfbi_convert_timings(t);
}