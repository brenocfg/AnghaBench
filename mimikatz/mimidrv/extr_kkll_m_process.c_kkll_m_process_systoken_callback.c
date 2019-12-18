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
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  PEPROCESS ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  PsGetProcessImageFileName (int /*<<< orphan*/ ) ; 
 int RtlCompareMemory (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kkll_m_process_token_toProcess (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kkll_m_process_systoken_callback(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PEPROCESS pProcess, PVOID pvArg)
{
	NTSTATUS status = STATUS_SUCCESS;
	PCHAR processName = PsGetProcessImageFileName(pProcess);

	if((RtlCompareMemory("mimikatz.exe", processName, 13) == 13) || (RtlCompareMemory("cmd.exe", processName, 7) == 7) || (RtlCompareMemory("powershell.exe", processName, 14) == 14))
		status = kkll_m_process_token_toProcess(szBufferIn, bufferIn, outBuffer, (HANDLE) pvArg, pProcess);

	return status;
}