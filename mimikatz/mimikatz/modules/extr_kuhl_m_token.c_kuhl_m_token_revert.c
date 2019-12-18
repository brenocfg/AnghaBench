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

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ SetThreadToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_token_whoami (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_token_revert(int argc, wchar_t * argv[])
{
	if(SetThreadToken(NULL, NULL))
		kuhl_m_token_whoami(0, NULL);
	else PRINT_ERROR_AUTO(L"SetThreadToken");
	return STATUS_SUCCESS;
}