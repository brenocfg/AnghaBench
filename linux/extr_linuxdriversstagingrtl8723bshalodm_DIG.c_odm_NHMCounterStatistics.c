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
typedef  int /*<<< orphan*/  PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  odm_GetNHMCounterStatistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_NHMCounterStatisticsReset (int /*<<< orphan*/ ) ; 

void odm_NHMCounterStatistics(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;

	/*  Get NHM report */
	odm_GetNHMCounterStatistics(pDM_Odm);

	/*  Reset NHM counter */
	odm_NHMCounterStatisticsReset(pDM_Odm);
}