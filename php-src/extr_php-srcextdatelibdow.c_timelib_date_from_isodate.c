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
 int* ml_table_common ; 
 int* ml_table_leap ; 
 int timelib_daynr_from_weeknr_ex (int,int,int,int*) ; 
 scalar_t__ timelib_is_leap (int) ; 

void timelib_date_from_isodate(timelib_sll iy, timelib_sll iw, timelib_sll id, timelib_sll *y, timelib_sll *m, timelib_sll *d)
{
	timelib_sll daynr = timelib_daynr_from_weeknr_ex(iy, iw, id, y) + 1;
	int *table;

	*m = 0;

	if (daynr <= 0) {
		*y += 1;
	}

	if (timelib_is_leap(*y)) {
		table = ml_table_leap;
		if (daynr > 366) {
			*y += 1;
			daynr -= 366;
		}
	} else {
		table = ml_table_common;
		if (daynr > 365) {
			*y += 1;
			daynr -= 365;
		}
	}

	do {
		daynr -= table[*m];
		(*m)++;
	} while (daynr > table[*m]);

	if (daynr <= 0) {
		daynr += 31;
		*y -= 1;
		*m = 12;
	}

	*d = daynr;
}