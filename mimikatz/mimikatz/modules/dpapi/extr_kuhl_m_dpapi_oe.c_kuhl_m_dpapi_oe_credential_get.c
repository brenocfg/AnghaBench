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
struct TYPE_7__ {int flags; int /*<<< orphan*/  guid; int /*<<< orphan*/  sid; } ;
struct TYPE_6__ {scalar_t__ Flink; } ;
struct TYPE_8__ {TYPE_2__ data; TYPE_1__ navigator; } ;
typedef  TYPE_3__* PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY ;
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ LPCGUID ;
typedef  int BOOL ;

/* Variables and functions */
 int KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_GUID ; 
 scalar_t__ RtlEqualGuid (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsicmp (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_5__ gDPAPI_Credentials ; 

PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY kuhl_m_dpapi_oe_credential_get(LPCWSTR sid, LPCGUID guid)
{
	PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY entry;
	BOOL cmpGuid, cmpSid;
	for(entry = (PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY) gDPAPI_Credentials.Flink; entry != (PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY) &gDPAPI_Credentials; entry = (PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY) entry->navigator.Flink)
	{
		cmpSid = sid && (_wcsicmp(sid, entry->data.sid) == 0);
		cmpGuid = guid && (entry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_GUID) && RtlEqualGuid(guid, &entry->data.guid);
		
		if(sid && guid)
		{
			if(cmpSid && cmpGuid)
				return entry;
		}
		else if (sid)
		{
			if(cmpSid && !(entry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_GUID))
				return entry;
		}
		else if(guid)
		{
			if(cmpGuid)
				return entry;
		}
	}
	return NULL;
}