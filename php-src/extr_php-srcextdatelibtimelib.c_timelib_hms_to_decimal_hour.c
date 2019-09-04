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

/* Variables and functions */

void timelib_hms_to_decimal_hour(int hour, int min, int sec, double *h)
{
	if (hour > 0) {
		*h = ((double)hour + (double)min / 60 + (double)sec / 3600);
	} else {
		*h = ((double)hour - (double)min / 60 - (double)sec / 3600);
	}
}