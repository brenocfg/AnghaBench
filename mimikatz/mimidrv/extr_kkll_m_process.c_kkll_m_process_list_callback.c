#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  Signer; int /*<<< orphan*/  Audit; int /*<<< orphan*/  Type; } ;
struct TYPE_4__ {TYPE_1__ Protection; int /*<<< orphan*/  SectionSignatureLevel; int /*<<< orphan*/  SignatureLevel; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PULONG ;
typedef  TYPE_2__* PKIWI_PROCESS_SIGNATURE_PROTECTION ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  scalar_t__ PEPROCESS ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__** EPROCESS_OffSetTable ; 
 size_t EprocessFlags2 ; 
 size_t KiwiOsIndex ; 
 size_t KiwiOsIndex_8 ; 
 size_t KiwiOsIndex_VISTA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int PROTECTED_PROCESS_MASK ; 
 int /*<<< orphan*/  PsGetProcessId (scalar_t__) ; 
 int /*<<< orphan*/  PsGetProcessImageFileName (scalar_t__) ; 
 size_t SignatureProtect ; 
 int TOKEN_FROZEN_MASK ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,...) ; 

NTSTATUS kkll_m_process_list_callback(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PEPROCESS pProcess, PVOID pvArg)
{
	NTSTATUS status;
	PKIWI_PROCESS_SIGNATURE_PROTECTION pSignatureProtect = NULL;
	PULONG pFlags2 = NULL;

	HANDLE processId = PsGetProcessId(pProcess);
	PCHAR processName = PsGetProcessImageFileName(pProcess);

	status = kprintf(outBuffer, L"%u\t%-14S", processId, processName);
	if(NT_SUCCESS(status))
	{
		if(KiwiOsIndex >= KiwiOsIndex_VISTA)
		{
			pFlags2 = (PULONG) (((ULONG_PTR) pProcess) + EPROCESS_OffSetTable[KiwiOsIndex][EprocessFlags2]);
			status = kprintf(outBuffer, L"\t%s", (*pFlags2 & TOKEN_FROZEN_MASK) ? L"F-Tok" : L"     ");
			if(NT_SUCCESS(status))
			{
				if(KiwiOsIndex >= KiwiOsIndex_8)
				{
					pSignatureProtect = (PKIWI_PROCESS_SIGNATURE_PROTECTION) (((ULONG_PTR) pProcess) + EPROCESS_OffSetTable[KiwiOsIndex][SignatureProtect]);
					status = kprintf(outBuffer, L"\tSig %02x/%02x", pSignatureProtect->SignatureLevel, pSignatureProtect->SectionSignatureLevel);
					if(NT_SUCCESS(status) && (KiwiOsIndex > KiwiOsIndex_8))
						status = kprintf(outBuffer, L" [%1x-%1x-%1x]", pSignatureProtect->Protection.Type, pSignatureProtect->Protection.Audit, pSignatureProtect->Protection.Signer);
				}
				else if(*pFlags2 & PROTECTED_PROCESS_MASK)
				{
					status = kprintf(outBuffer, L"\tP-Proc");
				}
			}
		}
		if(NT_SUCCESS(status))
			kprintf(outBuffer, L"\n");
	}
	return status;
}