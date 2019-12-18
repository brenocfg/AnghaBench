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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_standard_sleep(int argc, wchar_t * argv[])
{
	DWORD dwMilliseconds = argc ? wcstoul(argv[0], NULL, 0) : 1000;
	kprintf(L"Sleep : %u ms... ", dwMilliseconds);
	Sleep(dwMilliseconds);
	kprintf(L"End !\n");
	return STATUS_SUCCESS;
}