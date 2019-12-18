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
 int /*<<< orphan*/  FindStartOfYear (int,int*,int*,int*,int*,int*) ; 
 int HALAKIM_PER_DAY ; 
 int HALAKIM_PER_LUNAR_CYCLE ; 
 int JEWISH_SDN_OFFSET ; 
 int Tishri1 (int,int,int) ; 
 int* monthsPerYear ; 

zend_long JewishToSdn(
						int year,
						int month,
						int day)
{
	zend_long sdn;
	int metonicCycle;
	int metonicYear;
	int tishri1;
	int tishri1After;
	zend_long moladDay;
	zend_long moladHalakim;
	int yearLength;
	int lengthOfAdarIAndII;

	if (year <= 0 || day <= 0 || day > 30) {
		return (0);
	}
	switch (month) {
		case 1:
		case 2:
			/* It is Tishri or Heshvan - don't need the year length. */
			FindStartOfYear(year, &metonicCycle, &metonicYear,
							&moladDay, &moladHalakim, &tishri1);
			if (month == 1) {
				sdn = tishri1 + day - 1;
			} else {
				sdn = tishri1 + day + 29;
			}
			break;

		case 3:
			/* It is Kislev - must find the year length. */

			/* Find the start of the year. */
			FindStartOfYear(year, &metonicCycle, &metonicYear,
							&moladDay, &moladHalakim, &tishri1);

			/* Find the end of the year. */
			moladHalakim += HALAKIM_PER_LUNAR_CYCLE * monthsPerYear[metonicYear];
			moladDay += moladHalakim / HALAKIM_PER_DAY;
			moladHalakim = moladHalakim % HALAKIM_PER_DAY;
			tishri1After = Tishri1((metonicYear + 1) % 19, moladDay, moladHalakim);

			yearLength = tishri1After - tishri1;

			if (yearLength == 355 || yearLength == 385) {
				sdn = tishri1 + day + 59;
			} else {
				sdn = tishri1 + day + 58;
			}
			break;

		case 4:
		case 5:
		case 6:
			/* It is Tevet, Shevat or Adar I - don't need the year length. */

			FindStartOfYear(year + 1, &metonicCycle, &metonicYear,
							&moladDay, &moladHalakim, &tishri1After);

			if (monthsPerYear[(year - 1) % 19] == 12) {
				lengthOfAdarIAndII = 29;
			} else {
				lengthOfAdarIAndII = 59;
			}

			if (month == 4) {
				sdn = tishri1After + day - lengthOfAdarIAndII - 237;
			} else if (month == 5) {
				sdn = tishri1After + day - lengthOfAdarIAndII - 208;
			} else {
				sdn = tishri1After + day - lengthOfAdarIAndII - 178;
			}
			break;

		default:
			/* It is Adar II or later - don't need the year length. */
			FindStartOfYear(year + 1, &metonicCycle, &metonicYear,
							&moladDay, &moladHalakim, &tishri1After);

			switch (month) {
				case 7:
					sdn = tishri1After + day - 207;
					break;
				case 8:
					sdn = tishri1After + day - 178;
					break;
				case 9:
					sdn = tishri1After + day - 148;
					break;
				case 10:
					sdn = tishri1After + day - 119;
					break;
				case 11:
					sdn = tishri1After + day - 89;
					break;
				case 12:
					sdn = tishri1After + day - 60;
					break;
				case 13:
					sdn = tishri1After + day - 30;
					break;
				default:
					return (0);
			}
	}
	return (sdn + JEWISH_SDN_OFFSET);
}