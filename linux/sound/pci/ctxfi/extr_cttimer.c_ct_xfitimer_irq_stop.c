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
struct hw {int /*<<< orphan*/  (* set_timer_tick ) (struct hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_timer_irq ) (struct hw*,int /*<<< orphan*/ ) ;} ;
struct ct_timer {scalar_t__ running; TYPE_1__* atc; } ;
struct TYPE_2__ {struct hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_xfitimer_irq_stop(struct ct_timer *atimer)
{
	if (atimer->running) {
		struct hw *hw = atimer->atc->hw;
		hw->set_timer_irq(hw, 0);
		hw->set_timer_tick(hw, 0);
		atimer->running = 0;
	}
}