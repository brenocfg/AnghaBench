#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/ * md4protectedhash; int /*<<< orphan*/ * sha1hash; int /*<<< orphan*/ * md4hash; int /*<<< orphan*/  sid; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  TYPE_2__* PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY ;
typedef  scalar_t__ LPCGUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_GUID ; 
 int KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_MD4 ; 
 int KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_MD4p ; 
 int KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_SHA1 ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credential_add (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kuhl_m_dpapi_oe_credential_copyEntryWithNewGuid(PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY entry, LPCGUID guid)
{
	BOOL status = FALSE;
	if(entry && guid && !(entry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_GUID))
		status = kuhl_m_dpapi_oe_credential_add(entry->data.sid, guid, (entry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_MD4) ? entry->data.md4hash : NULL, (entry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_SHA1) ? entry->data.sha1hash : NULL, (entry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_MD4p) ? entry->data.md4protectedhash : NULL, NULL);
	return status;
}