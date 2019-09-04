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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_REG_TMR1CTL ; 
 int TMR1CTL_ENABLE ; 
 int rt_wdt_r32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7621_wdt_is_running(struct watchdog_device *w)
{
	return !!(rt_wdt_r32(TIMER_REG_TMR1CTL) & TMR1CTL_ENABLE);
}