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
typedef  int zend_long ;

/* Variables and functions */
 int DAYS_PER_4_YEARS ; 
 int DAYS_PER_5_MONTHS ; 
 int JULIAN_SDN_OFFSET ; 

zend_long JulianToSdn(
						int inputYear,
						int inputMonth,
						int inputDay)
{
	zend_long year;
	int month;

	/* check for invalid dates */
	if (inputYear == 0 || inputYear < -4713 ||
		inputMonth <= 0 || inputMonth > 12 ||
		inputDay <= 0 || inputDay > 31) {
		return (0);
	}
	/* check for dates before SDN 1 (Jan 2, 4713 B.C.) */
	if (inputYear == -4713) {
		if (inputMonth == 1 && inputDay == 1) {
			return (0);
		}
	}
	/* Make year always a positive number. */
	if (inputYear < 0) {
		year = inputYear + 4801;
	} else {
		year = inputYear + 4800;
	}

	/* Adjust the start of the year. */
	if (inputMonth > 2) {
		month = inputMonth - 3;
	} else {
		month = inputMonth + 9;
		year--;
	}

	return ((year * DAYS_PER_4_YEARS) / 4
			+ (month * DAYS_PER_5_MONTHS + 2) / 5
			+ inputDay
			- JULIAN_SDN_OFFSET);
}