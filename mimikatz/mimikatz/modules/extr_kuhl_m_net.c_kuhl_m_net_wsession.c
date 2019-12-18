#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {scalar_t__ wkui1_oth_domains; int /*<<< orphan*/  wkui1_logon_server; int /*<<< orphan*/  wkui1_logon_domain; int /*<<< orphan*/  wkui1_username; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  TYPE_1__* LPWKSTA_USER_INFO_1 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetWkstaUserEnum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,...) ; 
 scalar_t__ wcslen (scalar_t__) ; 

NTSTATUS kuhl_m_net_wsession(int argc, wchar_t * argv[])
{
	LPWKSTA_USER_INFO_1 pBuf;
	DWORD dwEntriesRead;
	DWORD dwTotalEntries;
	DWORD dwResumeHandle = 0;
	DWORD i;
	NET_API_STATUS nStatus;
	do
	{
		nStatus = NetWkstaUserEnum (argc ? argv[0] : NULL, 1, (LPBYTE*) &pBuf, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);
		if((nStatus == 0) || (nStatus == ERROR_MORE_DATA))
		{
			for (i = 0; i < dwEntriesRead; i++)
			{
				kprintf(L"\n"
					L"Username   : %s\n"
					L"Domain     : %s\n"
					L"LogonServer: %s\n",
					pBuf[i].wkui1_username, pBuf[i].wkui1_logon_domain, pBuf[i].wkui1_logon_server);
				if(pBuf[i].wkui1_oth_domains && wcslen(pBuf[i].wkui1_oth_domains))
					kprintf(L"OthDomains : %s\n", pBuf[i].wkui1_oth_domains);
			}
			NetApiBufferFree(pBuf);
		}
		else PRINT_ERROR(L"NetWkstaUserEnum: %08x\n", nStatus);
	}
	while (nStatus == ERROR_MORE_DATA);
	return STATUS_SUCCESS;
}