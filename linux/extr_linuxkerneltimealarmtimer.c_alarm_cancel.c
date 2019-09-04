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
struct alarm {int dummy; } ;

/* Variables and functions */
 int alarm_try_to_cancel (struct alarm*) ; 
 int /*<<< orphan*/  cpu_relax () ; 

int alarm_cancel(struct alarm *alarm)
{
	for (;;) {
		int ret = alarm_try_to_cancel(alarm);
		if (ret >= 0)
			return ret;
		cpu_relax();
	}
}