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
struct hrtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel_wait_running (struct hrtimer*) ; 
 int hrtimer_try_to_cancel (struct hrtimer*) ; 

int hrtimer_cancel(struct hrtimer *timer)
{
	int ret;

	do {
		ret = hrtimer_try_to_cancel(timer);

		if (ret < 0)
			hrtimer_cancel_wait_running(timer);
	} while (ret < 0);
	return ret;
}