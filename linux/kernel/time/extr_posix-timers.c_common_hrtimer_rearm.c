#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hrtimer {TYPE_3__* base; } ;
struct TYPE_4__ {struct hrtimer timer; } ;
struct TYPE_5__ {TYPE_1__ real; } ;
struct k_itimer {int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_overrun; TYPE_2__ it; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_time ) () ;} ;

/* Variables and functions */
 scalar_t__ hrtimer_forward (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_restart (struct hrtimer*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void common_hrtimer_rearm(struct k_itimer *timr)
{
	struct hrtimer *timer = &timr->it.real.timer;

	timr->it_overrun += hrtimer_forward(timer, timer->base->get_time(),
					    timr->it_interval);
	hrtimer_restart(timer);
}