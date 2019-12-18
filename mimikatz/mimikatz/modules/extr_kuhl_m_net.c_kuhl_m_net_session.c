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
struct TYPE_3__ {int /*<<< orphan*/  sesi10_idle_time; int /*<<< orphan*/  sesi10_time; int /*<<< orphan*/  sesi10_username; int /*<<< orphan*/  sesi10_cname; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  TYPE_1__* LPSESSION_INFO_10 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetSessionEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_net_session(int argc, wchar_t * argv[])
{
	LPSESSION_INFO_10 pBuf;
	DWORD dwEntriesRead;
	DWORD dwTotalEntries;
	DWORD dwResumeHandle = 0;
	DWORD i;
	NET_API_STATUS nStatus;
	do
	{
		nStatus = NetSessionEnum(argc ? argv[0] : NULL, NULL, NULL, 10, (LPBYTE*) &pBuf, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);
		if((nStatus == 0) || (nStatus == ERROR_MORE_DATA))
		{
			for (i = 0; i < dwEntriesRead; i++)
				kprintf(L"\n"
					L"Client  : %s\n"
					L"Username: %s\n"
					L"Active  : %u\n"
					L"Idle    : %u\n",
					pBuf[i].sesi10_cname, pBuf[i].sesi10_username, pBuf[i].sesi10_time, pBuf[i].sesi10_idle_time);
			NetApiBufferFree(pBuf);
		}
		else PRINT_ERROR(L"NetSessionEnum: %08x\n", nStatus);
	}
	while (nStatus == ERROR_MORE_DATA);
	return STATUS_SUCCESS;
}