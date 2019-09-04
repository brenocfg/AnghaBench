#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SupportAbility; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int ODM_BB_RSSI_MONITOR ; 
 int /*<<< orphan*/  odm_RSSIMonitorCheckCE (TYPE_1__*) ; 

void odm_RSSIMonitorCheck(PDM_ODM_T pDM_Odm)
{
	if (!(pDM_Odm->SupportAbility & ODM_BB_RSSI_MONITOR))
		return;

	odm_RSSIMonitorCheckCE(pDM_Odm);

}