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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  COMPUTER_NAME_FORMAT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ComputerNamePhysicalDnsFullyQualified ; 
 int /*<<< orphan*/  ComputerNamePhysicalNetBIOS ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetComputerNameEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 

BOOL kull_m_net_getComputerName(BOOL isFull, LPWSTR *name)
{
	BOOL status = FALSE;
	COMPUTER_NAME_FORMAT ft = isFull ? ComputerNamePhysicalDnsFullyQualified : ComputerNamePhysicalNetBIOS;
	DWORD dwSize = 0;
	if(!GetComputerNameEx(ft, NULL, &dwSize) && (GetLastError() == ERROR_MORE_DATA))
	{
		if(*name = (wchar_t *) LocalAlloc(LPTR, dwSize * sizeof(wchar_t)))
		{
			if(!(status = GetComputerNameEx(ft, *name, &dwSize)))
			{
				PRINT_ERROR_AUTO(L"GetComputerNameEx(data)");
				LocalFree(*name);
			}
		}
	}
	else PRINT_ERROR_AUTO(L"GetComputerNameEx(init)");
	return status;
}