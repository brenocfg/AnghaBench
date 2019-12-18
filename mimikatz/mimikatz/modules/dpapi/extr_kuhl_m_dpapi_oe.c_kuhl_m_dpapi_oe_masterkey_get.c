#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ Flink; } ;
struct TYPE_7__ {int /*<<< orphan*/  guid; } ;
struct TYPE_6__ {scalar_t__ Flink; } ;
struct TYPE_8__ {TYPE_2__ data; TYPE_1__ navigator; } ;
typedef  TYPE_3__* PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY ;
typedef  int /*<<< orphan*/  LPCGUID ;

/* Variables and functions */
 scalar_t__ RtlEqualGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ gDPAPI_Masterkeys ; 

PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY kuhl_m_dpapi_oe_masterkey_get(LPCGUID guid)
{
	PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY entry;
	for(entry = (PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY) gDPAPI_Masterkeys.Flink; entry != (PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY) &gDPAPI_Masterkeys; entry = (PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY) entry->navigator.Flink)
		if(RtlEqualGuid(guid, &entry->data.guid))
			return entry;
	return NULL;
}