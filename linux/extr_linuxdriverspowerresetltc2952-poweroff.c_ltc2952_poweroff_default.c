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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct ltc2952_poweroff {long wde_interval; TYPE_1__ timer_wde; TYPE_1__ timer_trigger; int /*<<< orphan*/  trigger_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int,long) ; 
 int /*<<< orphan*/  ltc2952_poweroff_timer_trigger ; 
 int /*<<< orphan*/  ltc2952_poweroff_timer_wde ; 

__attribute__((used)) static void ltc2952_poweroff_default(struct ltc2952_poweroff *data)
{
	data->wde_interval = 300L * 1E6L;
	data->trigger_delay = ktime_set(2, 500L*1E6L);

	hrtimer_init(&data->timer_trigger, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	data->timer_trigger.function = ltc2952_poweroff_timer_trigger;

	hrtimer_init(&data->timer_wde, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	data->timer_wde.function = ltc2952_poweroff_timer_wde;
}