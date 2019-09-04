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
struct hw {int /*<<< orphan*/  (* set_timer_irq ) (struct hw*,int) ;int /*<<< orphan*/  (* set_timer_tick ) (struct hw*,int) ;} ;
struct ct_timer {int running; TYPE_1__* atc; } ;
struct TYPE_2__ {struct hw* hw; } ;

/* Variables and functions */
 int MAX_TICKS ; 
 int /*<<< orphan*/  stub1 (struct hw*,int) ; 
 int /*<<< orphan*/  stub2 (struct hw*,int) ; 

__attribute__((used)) static void ct_xfitimer_irq_rearm(struct ct_timer *atimer, int ticks)
{
	struct hw *hw = atimer->atc->hw;
	if (ticks > MAX_TICKS)
		ticks = MAX_TICKS;
	hw->set_timer_tick(hw, ticks);
	if (!atimer->running)
		hw->set_timer_irq(hw, 1);
	atimer->running = 1;
}