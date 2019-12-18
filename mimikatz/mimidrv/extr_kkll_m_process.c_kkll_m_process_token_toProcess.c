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
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  Token; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PULONG ;
typedef  TYPE_1__ PROCESS_ACCESS_TOKEN ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  scalar_t__ PEPROCESS ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__** EPROCESS_OffSetTable ; 
 size_t EprocessFlags2 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KernelMode ; 
 size_t KiwiOsIndex ; 
 size_t KiwiOsIndex_VISTA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_KERNEL_HANDLE ; 
 int /*<<< orphan*/  ObOpenObjectByPointer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcessAccessToken ; 
 int /*<<< orphan*/  PsGetProcessId (scalar_t__) ; 
 int /*<<< orphan*/  PsGetProcessImageFileName (scalar_t__) ; 
 int /*<<< orphan*/ * PsProcessType ; 
 int TOKEN_FROZEN_MASK ; 
 int /*<<< orphan*/  TokenPrimary ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZwDuplicateToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZwSetInformationProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

NTSTATUS kkll_m_process_token_toProcess(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, HANDLE hSrcToken, PEPROCESS pToProcess)
{
	PROCESS_ACCESS_TOKEN ProcessTokenInformation = {NULL, NULL};
	HANDLE hToProcess;
	PULONG pFlags2 = NULL;
	NTSTATUS status;
	HANDLE processId = PsGetProcessId(pToProcess);
	PCHAR processName = PsGetProcessImageFileName(pToProcess);

	status = ObOpenObjectByPointer(pToProcess, OBJ_KERNEL_HANDLE, NULL, 0, *PsProcessType, KernelMode, &hToProcess);
	if(NT_SUCCESS(status))
	{
		status = ZwDuplicateToken(hSrcToken, 0, NULL, FALSE, TokenPrimary, &ProcessTokenInformation.Token);
		if(NT_SUCCESS(status))
		{
			if(KiwiOsIndex >= KiwiOsIndex_VISTA)
			{
				pFlags2 = (PULONG) (((ULONG_PTR) pToProcess) + EPROCESS_OffSetTable[KiwiOsIndex][EprocessFlags2]);
				if(*pFlags2 & TOKEN_FROZEN_MASK)
					*pFlags2 &= ~TOKEN_FROZEN_MASK;
				else
					pFlags2 = NULL;
			}

			status = ZwSetInformationProcess(hToProcess, ProcessAccessToken, &ProcessTokenInformation, sizeof(PROCESS_ACCESS_TOKEN));
			if(NT_SUCCESS(status))
				status = kprintf(outBuffer, L" * to %u/%-14S\n", processId, processName);
			else
				status = kprintf(outBuffer, L" ! ZwSetInformationProcess 0x%08x for %u/%-14S\n", status, processId, processName);

			if((KiwiOsIndex >= KiwiOsIndex_VISTA) && pFlags2)
				*pFlags2 |= TOKEN_FROZEN_MASK;

			ZwClose(ProcessTokenInformation.Token);
		}
		ZwClose(hToProcess);
	}
	return status;
}