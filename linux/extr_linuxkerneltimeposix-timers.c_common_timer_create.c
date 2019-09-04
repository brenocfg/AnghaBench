#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {TYPE_1__ real; } ;
struct k_itimer {int /*<<< orphan*/  it_clock; TYPE_2__ it; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int common_timer_create(struct k_itimer *new_timer)
{
	hrtimer_init(&new_timer->it.real.timer, new_timer->it_clock, 0);
	return 0;
}