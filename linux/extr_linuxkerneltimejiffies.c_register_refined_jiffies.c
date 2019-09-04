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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {char* name; int mult; int /*<<< orphan*/  rating; } ;

/* Variables and functions */
 int HZ ; 
 int JIFFIES_SHIFT ; 
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  __clocksource_register (TYPE_1__*) ; 
 TYPE_1__ clocksource_jiffies ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 TYPE_1__ refined_jiffies ; 

int register_refined_jiffies(long cycles_per_second)
{
	u64 nsec_per_tick, shift_hz;
	long cycles_per_tick;



	refined_jiffies = clocksource_jiffies;
	refined_jiffies.name = "refined-jiffies";
	refined_jiffies.rating++;

	/* Calc cycles per tick */
	cycles_per_tick = (cycles_per_second + HZ/2)/HZ;
	/* shift_hz stores hz<<8 for extra accuracy */
	shift_hz = (u64)cycles_per_second << 8;
	shift_hz += cycles_per_tick/2;
	do_div(shift_hz, cycles_per_tick);
	/* Calculate nsec_per_tick using shift_hz */
	nsec_per_tick = (u64)NSEC_PER_SEC << 8;
	nsec_per_tick += (u32)shift_hz/2;
	do_div(nsec_per_tick, (u32)shift_hz);

	refined_jiffies.mult = ((u32)nsec_per_tick) << JIFFIES_SHIFT;

	__clocksource_register(&refined_jiffies);
	return 0;
}