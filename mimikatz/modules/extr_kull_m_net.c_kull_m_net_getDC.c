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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {scalar_t__ DomainControllerName; } ;
typedef  TYPE_1__* PDOMAIN_CONTROLLER_INFO ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DS_IS_DNS_NAME ; 
 scalar_t__ DS_RETURN_DNS_NAME ; 
 scalar_t__ DsGetDcName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__**) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ wcslen (scalar_t__) ; 

BOOL kull_m_net_getDC(LPCWSTR fullDomainName, DWORD altFlags, LPWSTR * fullDCName)
{
	BOOL status = FALSE;
	DWORD ret, size;
	PDOMAIN_CONTROLLER_INFO cInfo = NULL;
	ret = DsGetDcName(NULL, fullDomainName, NULL, NULL, altFlags | DS_IS_DNS_NAME | DS_RETURN_DNS_NAME, &cInfo);
	if(ret == ERROR_SUCCESS)
	{
		size = (DWORD) (wcslen(cInfo->DomainControllerName + 2) + 1) * sizeof(wchar_t);
		if(*fullDCName = (wchar_t *) LocalAlloc(LPTR, size))
		{
			status = TRUE;
			RtlCopyMemory(*fullDCName, cInfo->DomainControllerName + 2, size);
		}
		NetApiBufferFree(cInfo);
	}
	else PRINT_ERROR(L"DsGetDcName: %u\n", ret);
	return status;
}