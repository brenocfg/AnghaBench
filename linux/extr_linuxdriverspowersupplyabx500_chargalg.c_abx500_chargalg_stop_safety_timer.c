#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int safety_timer_expired; } ;
struct abx500_chargalg {TYPE_1__ events; int /*<<< orphan*/  safety_timer; } ;

/* Variables and functions */
 scalar_t__ hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void abx500_chargalg_stop_safety_timer(struct abx500_chargalg *di)
{
	if (hrtimer_try_to_cancel(&di->safety_timer) >= 0)
		di->events.safety_timer_expired = false;
}