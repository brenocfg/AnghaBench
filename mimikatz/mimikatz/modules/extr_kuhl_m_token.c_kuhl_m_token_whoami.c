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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_NO_TOKEN ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenThreadToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_token_displayAccount (int /*<<< orphan*/ ,int) ; 

NTSTATUS kuhl_m_token_whoami(int argc, wchar_t * argv[])
{
	HANDLE hToken;
	kprintf(L" * Process Token : ");
	if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		kuhl_m_token_displayAccount(hToken, argc);
		CloseHandle(hToken);
	}
	else PRINT_ERROR_AUTO(L"OpenProcessToken");

	kprintf(L" * Thread Token  : ");
	if(OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, TRUE, &hToken))
	{
		kuhl_m_token_displayAccount(hToken, argc);
		CloseHandle(hToken);
	}
	else if(GetLastError() == ERROR_NO_TOKEN)
		kprintf(L"no token\n");
	else PRINT_ERROR_AUTO(L"OpenThreadToken");

	return STATUS_SUCCESS;
}