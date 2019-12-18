#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {scalar_t__ toProcessId; scalar_t__ fromProcessId; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PMIMIDRV_PROCESS_TOKEN_FROM_TO ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  scalar_t__ PEPROCESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  MIMIDRV_PROCESS_TOKEN_FROM_TO ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  KernelMode ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_KERNEL_HANDLE ; 
 int /*<<< orphan*/  ObDereferenceObject (scalar_t__) ; 
 int /*<<< orphan*/  ObOpenObjectByPointer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PsGetProcessId (scalar_t__) ; 
 int /*<<< orphan*/  PsGetProcessImageFileName (scalar_t__) ; 
 scalar_t__ PsInitialSystemProcess ; 
 int /*<<< orphan*/  PsLookupProcessByProcessId (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * PsProcessType ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZwOpenProcessTokenEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kkll_m_process_enum (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kkll_m_process_systoken_callback ; 
 int /*<<< orphan*/  kkll_m_process_token_toProcess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kkll_m_process_token(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer)
{
	NTSTATUS status = STATUS_SUCCESS;
	PMIMIDRV_PROCESS_TOKEN_FROM_TO pTokenFromTo = (PMIMIDRV_PROCESS_TOKEN_FROM_TO) bufferIn;
	ULONG fromProcessId, toProcessId;
	HANDLE hFromProcess, hFromProcessToken;
	PEPROCESS pFromProcess = PsInitialSystemProcess, pToProcess = NULL;

	if(pTokenFromTo && (szBufferIn == sizeof(MIMIDRV_PROCESS_TOKEN_FROM_TO)))
	{
		if(pTokenFromTo->fromProcessId)
			status = PsLookupProcessByProcessId((HANDLE) pTokenFromTo->fromProcessId, &pFromProcess);
		if(NT_SUCCESS(status) && pTokenFromTo->toProcessId)
			status = PsLookupProcessByProcessId((HANDLE) pTokenFromTo->toProcessId, &pToProcess);
	}

	if(NT_SUCCESS(status))
	{
		status = ObOpenObjectByPointer(pFromProcess, OBJ_KERNEL_HANDLE, NULL, 0, *PsProcessType, KernelMode, &hFromProcess);
		if(NT_SUCCESS(status))
		{
			status = ZwOpenProcessTokenEx(hFromProcess, 0, OBJ_KERNEL_HANDLE, &hFromProcessToken);
			if(NT_SUCCESS(status))
			{
				status = kprintf(outBuffer, L"Token from %u/%-14S\n", PsGetProcessId(pFromProcess), PsGetProcessImageFileName(pFromProcess));
				if(NT_SUCCESS(status))
				{
					if(pToProcess)
						status = kkll_m_process_token_toProcess(szBufferIn, bufferIn, outBuffer, hFromProcessToken, pToProcess);
					else
						status = kkll_m_process_enum(szBufferIn, bufferIn, outBuffer, kkll_m_process_systoken_callback, hFromProcessToken);
				}
				ZwClose(hFromProcessToken);
			}
			ZwClose(hFromProcess);
		}
	}

	if(pToProcess)
		ObDereferenceObject(pToProcess);

	if(pFromProcess && (pFromProcess != PsInitialSystemProcess))
		ObDereferenceObject(pFromProcess);

	return status;
}