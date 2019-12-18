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
 scalar_t__ hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  j1939_ecu_put (struct j1939_ecu*) ; 

void j1939_ecu_timer_cancel(struct j1939_ecu *ecu)
{
	if (hrtimer_cancel(&ecu->ac_timer))
		j1939_ecu_put(ecu);
}