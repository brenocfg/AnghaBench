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
typedef  int timelib_sll ;

/* Variables and functions */

int timelib_valid_time(timelib_sll h, timelib_sll i, timelib_sll s)
{
	if (h < 0 || h > 23 || i < 0 || i > 59 || s < 0 || s > 59) {
		return 0;
	}
	return 1;
}