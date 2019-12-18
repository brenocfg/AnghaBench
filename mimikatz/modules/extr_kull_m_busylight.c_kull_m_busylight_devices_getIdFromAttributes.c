#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ Vid; scalar_t__ Pid; } ;
struct TYPE_7__ {scalar_t__ VendorID; scalar_t__ ProductID; } ;
typedef  TYPE_1__* PHIDD_ATTRIBUTES ;
typedef  TYPE_2__* PCBUSYLIGHT_DEVICE_ID ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_2__*) ; 
 TYPE_2__* KULL_M_BUSYLIGHT_CATALOG ; 

PCBUSYLIGHT_DEVICE_ID kull_m_busylight_devices_getIdFromAttributes(PHIDD_ATTRIBUTES attributes)
{
	DWORD i;
	if(attributes)
		for(i = 0; i < ARRAYSIZE(KULL_M_BUSYLIGHT_CATALOG); i++)
			if((KULL_M_BUSYLIGHT_CATALOG[i].Vid == attributes->VendorID) && (KULL_M_BUSYLIGHT_CATALOG[i].Pid == attributes->ProductID))
				return &KULL_M_BUSYLIGHT_CATALOG[i];
	return NULL;
}