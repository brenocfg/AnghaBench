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
 int ceil (double) ; 
 int floor (double) ; 

void timelib_decimal_hour_to_hms(double h, int *hour, int *min, int *sec)
{
	if (h > 0) {
		*hour = floor(h);
		*min = floor((h - *hour) * 60);
		*sec = (h - *hour - ((float) *min / 60)) * 3600;
	} else {
		*hour = ceil(h);
		*min = 0 - ceil((h - *hour) * 60);
		*sec = 0 - (h - *hour - ((float) *min / -60)) * 3600;
	}
}