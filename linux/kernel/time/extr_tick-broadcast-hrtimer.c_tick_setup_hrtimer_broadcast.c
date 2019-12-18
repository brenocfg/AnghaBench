#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS_HARD ; 
 int /*<<< orphan*/  bc_handler ; 
 TYPE_1__ bctimer ; 
 int /*<<< orphan*/  ce_broadcast_hrtimer ; 
 int /*<<< orphan*/  clockevents_register_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tick_setup_hrtimer_broadcast(void)
{
	hrtimer_init(&bctimer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	bctimer.function = bc_handler;
	clockevents_register_device(&ce_broadcast_hrtimer);
}