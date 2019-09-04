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
typedef  scalar_t__ timelib_sll ;

/* Variables and functions */

double timelib_ts_to_julianday(timelib_sll ts)
{
	double tmp;

	tmp = (double) ts;
	tmp /= (double) 86400;
	tmp += (double) 2440587.5;

	return tmp;
}