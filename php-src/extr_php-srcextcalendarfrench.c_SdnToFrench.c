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
 scalar_t__ DAYS_PER_4_YEARS ; 
 int DAYS_PER_MONTH ; 
 scalar_t__ FIRST_VALID ; 
 scalar_t__ FRENCH_SDN_OFFSET ; 
 scalar_t__ LAST_VALID ; 

void SdnToFrench(
					zend_long sdn,
					int *pYear,
					int *pMonth,
					int *pDay)
{
	zend_long temp;
	int dayOfYear;

	if (sdn < FIRST_VALID || sdn > LAST_VALID) {
		*pYear = 0;
		*pMonth = 0;
		*pDay = 0;
		return;
	}
	temp = (sdn - FRENCH_SDN_OFFSET) * 4 - 1;
	*pYear = temp / DAYS_PER_4_YEARS;
	dayOfYear = (temp % DAYS_PER_4_YEARS) / 4;
	*pMonth = dayOfYear / DAYS_PER_MONTH + 1;
	*pDay = dayOfYear % DAYS_PER_MONTH + 1;
}