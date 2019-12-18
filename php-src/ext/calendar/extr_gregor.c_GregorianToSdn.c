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
 int DAYS_PER_400_YEARS ; 
 int DAYS_PER_4_YEARS ; 
 int DAYS_PER_5_MONTHS ; 
 int GREGOR_SDN_OFFSET ; 

zend_long GregorianToSdn(
						   int inputYear,
						   int inputMonth,
						   int inputDay)
{
	zend_long year;
	int month;

	/* check for invalid dates */
	if (inputYear == 0 || inputYear < -4714 ||
		inputMonth <= 0 || inputMonth > 12 ||
		inputDay <= 0 || inputDay > 31) {
		return (0);
	}
	/* check for dates before SDN 1 (Nov 25, 4714 B.C.) */
	if (inputYear == -4714) {
		if (inputMonth < 11) {
			return (0);
		}
		if (inputMonth == 11 && inputDay < 25) {
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

	return (((year / 100) * DAYS_PER_400_YEARS) / 4
			+ ((year % 100) * DAYS_PER_4_YEARS) / 4
			+ (month * DAYS_PER_5_MONTHS + 2) / 5
			+ inputDay
			- GREGOR_SDN_OFFSET);
}