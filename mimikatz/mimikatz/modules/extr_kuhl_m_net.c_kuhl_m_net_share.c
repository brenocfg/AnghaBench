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
struct TYPE_3__ {int /*<<< orphan*/  shi502_path; int /*<<< orphan*/  shi502_max_uses; int /*<<< orphan*/  shi502_current_uses; int /*<<< orphan*/  shi502_type; int /*<<< orphan*/  shi502_netname; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  TYPE_1__* LPSHARE_INFO_502 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetShareEnum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kuhl_m_net_share_type (int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_net_share(int argc, wchar_t * argv[])
{
	LPSHARE_INFO_502 pBuf;
	DWORD dwEntriesRead;
	DWORD dwTotalEntries;
	DWORD dwResumeHandle = 0;
	DWORD i;
	NET_API_STATUS nStatus;
	do
	{
		nStatus = NetShareEnum (argc ? argv[0] : NULL, 502, (LPBYTE*) &pBuf, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, &dwResumeHandle);
		if((nStatus == 0) || (nStatus == ERROR_MORE_DATA))
		{
			for (i = 0; i < dwEntriesRead; i++)
			{
				kprintf(L"\n"
					L"Netname : %s\n"
					L"Type    : %08x - ",
					pBuf[i].shi502_netname, pBuf[i].shi502_type);
				kuhl_m_net_share_type(pBuf[i].shi502_type);
				kprintf(
					L"Uses    : %u/%u\n"
					L"Path    : %s\n",
					pBuf[i].shi502_current_uses, pBuf[i].shi502_max_uses, pBuf[i].shi502_path);
			}
			NetApiBufferFree(pBuf);
		}
		else PRINT_ERROR(L"NetShareEnum: %08x\n", nStatus);
	}
	while (nStatus == ERROR_MORE_DATA);
	return STATUS_SUCCESS;
}