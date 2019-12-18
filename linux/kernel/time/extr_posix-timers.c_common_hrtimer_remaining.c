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
struct hrtimer {int dummy; } ;
struct TYPE_3__ {struct hrtimer timer; } ;
struct TYPE_4__ {TYPE_1__ real; } ;
struct k_itimer {TYPE_2__ it; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  __hrtimer_expires_remaining_adjusted (struct hrtimer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t common_hrtimer_remaining(struct k_itimer *timr, ktime_t now)
{
	struct hrtimer *timer = &timr->it.real.timer;

	return __hrtimer_expires_remaining_adjusted(timer, now);
}