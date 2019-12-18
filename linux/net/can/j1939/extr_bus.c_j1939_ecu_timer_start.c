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
struct j1939_ecu {int /*<<< orphan*/  ac_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_SOFT ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_ecu_get (struct j1939_ecu*) ; 
 int /*<<< orphan*/  ms_to_ktime (int) ; 

void j1939_ecu_timer_start(struct j1939_ecu *ecu)
{
	/* The ECU is held here and released in the
	 * j1939_ecu_timer_handler() or j1939_ecu_timer_cancel().
	 */
	j1939_ecu_get(ecu);

	/* Schedule timer in 250 msec to commit address change. */
	hrtimer_start(&ecu->ac_timer, ms_to_ktime(250),
		      HRTIMER_MODE_REL_SOFT);
}