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
typedef  int u32 ;
struct watchdog_device {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_REG_TMR1CTL ; 
 int TMR1CTL_ENABLE ; 
 int TMR1CTL_PRESCALE_SHIFT ; 
 int /*<<< orphan*/  mt7621_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int rt_wdt_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_wdt_w32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt7621_wdt_start(struct watchdog_device *w)
{
	u32 t;

	/* set the prescaler to 1ms == 1000us */
	rt_wdt_w32(TIMER_REG_TMR1CTL, 1000 << TMR1CTL_PRESCALE_SHIFT);

	mt7621_wdt_set_timeout(w, w->timeout);

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t |= TMR1CTL_ENABLE;
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	return 0;
}