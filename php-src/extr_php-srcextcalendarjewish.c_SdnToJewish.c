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
typedef  scalar_t__ zend_long ;

/* Variables and functions */
 int /*<<< orphan*/  FindTishriMolad (scalar_t__,int*,int*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ HALAKIM_PER_DAY ; 
 scalar_t__ HALAKIM_PER_LUNAR_CYCLE ; 
 scalar_t__ JEWISH_SDN_MAX ; 
 scalar_t__ JEWISH_SDN_OFFSET ; 
 int Tishri1 (int,scalar_t__,scalar_t__) ; 
 scalar_t__* monthsPerYear ; 

void SdnToJewish(
					zend_long sdn,
					int *pYear,
					int *pMonth,
					int *pDay)
{
	zend_long inputDay;
	zend_long day;
	zend_long halakim;
	int metonicCycle;
	int metonicYear;
	int tishri1;
	int tishri1After;
	int yearLength;

	if (sdn <= JEWISH_SDN_OFFSET || sdn > JEWISH_SDN_MAX) {
		*pYear = 0;
		*pMonth = 0;
		*pDay = 0;
		return;
	}
	inputDay = sdn - JEWISH_SDN_OFFSET;

	FindTishriMolad(inputDay, &metonicCycle, &metonicYear, &day, &halakim);
	tishri1 = Tishri1(metonicYear, day, halakim);

	if (inputDay >= tishri1) {
		/* It found Tishri 1 at the start of the year. */
		*pYear = metonicCycle * 19 + metonicYear + 1;
		if (inputDay < tishri1 + 59) {
			if (inputDay < tishri1 + 30) {
				*pMonth = 1;
				*pDay = inputDay - tishri1 + 1;
			} else {
				*pMonth = 2;
				*pDay = inputDay - tishri1 - 29;
			}
			return;
		}
		/* We need the length of the year to figure this out, so find
		 * Tishri 1 of the next year. */
		halakim += HALAKIM_PER_LUNAR_CYCLE * monthsPerYear[metonicYear];
		day += halakim / HALAKIM_PER_DAY;
		halakim = halakim % HALAKIM_PER_DAY;
		tishri1After = Tishri1((metonicYear + 1) % 19, day, halakim);
	} else {
		/* It found Tishri 1 at the end of the year. */
		*pYear = metonicCycle * 19 + metonicYear;
		if (inputDay >= tishri1 - 177) {
			/* It is one of the last 6 months of the year. */
			if (inputDay > tishri1 - 30) {
				*pMonth = 13;
				*pDay = inputDay - tishri1 + 30;
			} else if (inputDay > tishri1 - 60) {
				*pMonth = 12;
				*pDay = inputDay - tishri1 + 60;
			} else if (inputDay > tishri1 - 89) {
				*pMonth = 11;
				*pDay = inputDay - tishri1 + 89;
			} else if (inputDay > tishri1 - 119) {
				*pMonth = 10;
				*pDay = inputDay - tishri1 + 119;
			} else if (inputDay > tishri1 - 148) {
				*pMonth = 9;
				*pDay = inputDay - tishri1 + 148;
			} else {
				*pMonth = 8;
				*pDay = inputDay - tishri1 + 178;
			}
			return;
		} else {
			if (monthsPerYear[(*pYear - 1) % 19] == 13) {
				*pMonth = 7;
				*pDay = inputDay - tishri1 + 207;
				if (*pDay > 0)
					return;
				(*pMonth)--;
				(*pDay) += 30;
				if (*pDay > 0)
					return;
				(*pMonth)--;
				(*pDay) += 30;
			} else {
				*pMonth = 7;
				*pDay = inputDay - tishri1 + 207;
				if (*pDay > 0)
					return;
				(*pMonth) -= 2;
				(*pDay) += 30;
			}
			if (*pDay > 0)
				return;
			(*pMonth)--;
			(*pDay) += 29;
			if (*pDay > 0)
				return;

			/* We need the length of the year to figure this out, so find
			 * Tishri 1 of this year. */
			tishri1After = tishri1;
			FindTishriMolad(day - 365,
							&metonicCycle, &metonicYear, &day, &halakim);
			tishri1 = Tishri1(metonicYear, day, halakim);
		}
	}

	yearLength = tishri1After - tishri1;
	day = inputDay - tishri1 - 29;
	if (yearLength == 355 || yearLength == 385) {
		/* Heshvan has 30 days */
		if (day <= 30) {
			*pMonth = 2;
			*pDay = day;
			return;
		}
		day -= 30;
	} else {
		/* Heshvan has 29 days */
		if (day <= 29) {
			*pMonth = 2;
			*pDay = day;
			return;
		}
		day -= 29;
	}

	/* It has to be Kislev. */
	*pMonth = 3;
	*pDay = day;
}