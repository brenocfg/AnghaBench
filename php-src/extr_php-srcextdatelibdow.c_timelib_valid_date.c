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
 int timelib_days_in_month (int,int) ; 

int timelib_valid_date(timelib_sll y, timelib_sll m, timelib_sll d)
{
	if (m < 1 || m > 12 || d < 1 || d > timelib_days_in_month(y, m)) {
		return 0;
	}
	return 1;
}