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
 int /*<<< orphan*/  MoladOfMetonicCycle (int,int*,int*) ; 
 int Tishri1 (int,int,int) ; 
 int* yearOffset ; 

__attribute__((used)) static void FindStartOfYear(
							   int year,
							   int *pMetonicCycle,
							   int *pMetonicYear,
							   zend_long *pMoladDay,
							   zend_long *pMoladHalakim,
							   int *pTishri1)
{
	*pMetonicCycle = (year - 1) / 19;
	*pMetonicYear = (year - 1) % 19;
	MoladOfMetonicCycle(*pMetonicCycle, pMoladDay, pMoladHalakim);

	*pMoladHalakim += HALAKIM_PER_LUNAR_CYCLE * yearOffset[*pMetonicYear];
	*pMoladDay += *pMoladHalakim / HALAKIM_PER_DAY;
	*pMoladHalakim = *pMoladHalakim % HALAKIM_PER_DAY;

	*pTishri1 = Tishri1(*pMetonicYear, *pMoladDay, *pMoladHalakim);
}