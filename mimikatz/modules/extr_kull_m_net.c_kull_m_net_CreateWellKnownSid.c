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
typedef  int /*<<< orphan*/  WELL_KNOWN_SID_TYPE ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWellKnownSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * LocalFree (int /*<<< orphan*/ *) ; 

BOOL kull_m_net_CreateWellKnownSid(WELL_KNOWN_SID_TYPE WellKnownSidType, PSID DomainSid, PSID * pSid)
{
	BOOL status = FALSE;
	DWORD szNeeded = 0, dwError;
	CreateWellKnownSid(WellKnownSidType, DomainSid, NULL, &szNeeded);
	dwError = GetLastError();
	if((dwError == ERROR_INVALID_PARAMETER) || (dwError == ERROR_INSUFFICIENT_BUFFER))
		if(*pSid = (PSID) LocalAlloc(LPTR, szNeeded))
			if(!(status = CreateWellKnownSid(WellKnownSidType, DomainSid, *pSid, &szNeeded)))
				*pSid = LocalFree(*pSid);
	return status;
}