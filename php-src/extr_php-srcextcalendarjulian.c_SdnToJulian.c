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
 long INT_MAX ; 
 long INT_MIN ; 
 int JULIAN_SDN_OFFSET ; 
 int LONG_MAX ; 
 int LONG_MIN ; 

void SdnToJulian(
					zend_long sdn,
					int *pYear,
					int *pMonth,
					int *pDay)
{
	int year;
	int month;
	int day;
	zend_long temp;
	int dayOfYear;

	if (sdn <= 0) {
		goto fail;
	}
	/* Check for overflow */
	if (sdn > (LONG_MAX - JULIAN_SDN_OFFSET * 4 + 1) / 4 || sdn < LONG_MIN / 4) {
		goto fail;
	}
	temp = sdn * 4 + (JULIAN_SDN_OFFSET * 4 - 1);

	/* Calculate the year and day of year (1 <= dayOfYear <= 366). */
	{
		long yearl = temp / DAYS_PER_4_YEARS;
		if (yearl > INT_MAX || yearl < INT_MIN) {
			goto fail;
		}
		year = (int) yearl;
	}
	dayOfYear = (temp % DAYS_PER_4_YEARS) / 4 + 1;

	/* Calculate the month and day of month. */
	temp = dayOfYear * 5 - 3;
	month = temp / DAYS_PER_5_MONTHS;
	day = (temp % DAYS_PER_5_MONTHS) / 5 + 1;

	/* Convert to the normal beginning of the year. */
	if (month < 10) {
		month += 3;
	} else {
		year += 1;
		month -= 9;
	}

	/* Adjust to the B.C./A.D. type numbering. */
	year -= 4800;
	if (year <= 0)
		year--;

	*pYear = year;
	*pMonth = month;
	*pDay = day;
	return;

fail:
	*pYear = 0;
	*pMonth = 0;
	*pDay = 0;
}