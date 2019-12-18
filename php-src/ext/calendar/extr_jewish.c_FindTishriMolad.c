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
 int HALAKIM_PER_DAY ; 
 int HALAKIM_PER_LUNAR_CYCLE ; 
 scalar_t__ HALAKIM_PER_METONIC_CYCLE ; 
 int /*<<< orphan*/  MoladOfMetonicCycle (int,int*,int*) ; 
 int* monthsPerYear ; 

__attribute__((used)) static void FindTishriMolad(
							   zend_long inputDay,
							   int *pMetonicCycle,
							   int *pMetonicYear,
							   zend_long *pMoladDay,
							   zend_long *pMoladHalakim)
{
	zend_long moladDay;
	zend_long moladHalakim;
	int metonicCycle;
	int metonicYear;

	/* Estimate the metonic cycle number.  Note that this may be an under
	 * estimate because there are 6939.6896 days in a metonic cycle not
	 * 6940, but it will never be an over estimate.  The loop below will
	 * correct for any error in this estimate. */
	metonicCycle = (inputDay + 310) / 6940;

	/* Calculate the time of the starting molad for this metonic cycle. */
	MoladOfMetonicCycle(metonicCycle, &moladDay, &moladHalakim);

	/* If the above was an under estimate, increment the cycle number until
	 * the correct one is found.  For modern dates this loop is about 98.6%
	 * likely to not execute, even once, because the above estimate is
	 * really quite close. */
	while (moladDay < inputDay - 6940 + 310) {
		metonicCycle++;
		moladHalakim += HALAKIM_PER_METONIC_CYCLE;
		moladDay += moladHalakim / HALAKIM_PER_DAY;
		moladHalakim = moladHalakim % HALAKIM_PER_DAY;
	}

	/* Find the molad of Tishri closest to this date. */
	for (metonicYear = 0; metonicYear < 18; metonicYear++) {
		if (moladDay > inputDay - 74) {
			break;
		}
		moladHalakim += HALAKIM_PER_LUNAR_CYCLE * monthsPerYear[metonicYear];
		moladDay += moladHalakim / HALAKIM_PER_DAY;
		moladHalakim = moladHalakim % HALAKIM_PER_DAY;
	}

	*pMetonicCycle = metonicCycle;
	*pMetonicYear = metonicYear;
	*pMoladDay = moladDay;
	*pMoladHalakim = moladHalakim;
}