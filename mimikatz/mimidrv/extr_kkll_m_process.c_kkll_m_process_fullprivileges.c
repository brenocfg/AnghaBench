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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int* Present; int* Enabled; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PKIWI_NT6_PRIVILEGES ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  scalar_t__ PEPROCESS ;
typedef  int /*<<< orphan*/ * PACCESS_TOKEN ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__** EPROCESS_OffSetTable ; 
 size_t KiwiOsIndex ; 
 size_t KiwiOsIndex_VISTA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (scalar_t__) ; 
 int /*<<< orphan*/  PsDereferencePrimaryToken (int /*<<< orphan*/ *) ; 
 scalar_t__ PsGetCurrentProcess () ; 
 int /*<<< orphan*/  PsGetProcessId (scalar_t__) ; 
 int /*<<< orphan*/  PsGetProcessImageFileName (scalar_t__) ; 
 int /*<<< orphan*/  PsLookupProcessByProcessId (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * PsReferencePrimaryToken (scalar_t__) ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 size_t TokenPrivs ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kkll_m_process_fullprivileges(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer)
{
	NTSTATUS status = STATUS_SUCCESS;
	PEPROCESS pProcess = NULL;
	PACCESS_TOKEN pAccessToken = NULL;
	PKIWI_NT6_PRIVILEGES pPrivileges;
	PULONG pPid = (PULONG) bufferIn;

	if(KiwiOsIndex >= KiwiOsIndex_VISTA)
	{
		if(pPid && (szBufferIn == sizeof(ULONG)))
			status = PsLookupProcessByProcessId((HANDLE) *pPid, &pProcess);
		else
			pProcess = PsGetCurrentProcess();

		if(NT_SUCCESS(status) && pProcess)
		{
			if(pAccessToken = PsReferencePrimaryToken(pProcess))
			{
				status = kprintf(outBuffer, L"All privileges for the access token from %u/%-14S\n", PsGetProcessId(pProcess), PsGetProcessImageFileName(pProcess));
				
				pPrivileges = (PKIWI_NT6_PRIVILEGES) (((ULONG_PTR) pAccessToken) + EPROCESS_OffSetTable[KiwiOsIndex][TokenPrivs]);
				pPrivileges->Present[0] = pPrivileges->Enabled[0] /*= pPrivileges->EnabledByDefault[0]*/ = 0xfc;
				pPrivileges->Present[1] = pPrivileges->Enabled[1] /*= pPrivileges->EnabledByDefault[1]*/ = //...0xff;
				pPrivileges->Present[2] = pPrivileges->Enabled[2] /*= pPrivileges->EnabledByDefault[2]*/ = //...0xff;
				pPrivileges->Present[3] = pPrivileges->Enabled[3] /*= pPrivileges->EnabledByDefault[3]*/ = 0xff;
				pPrivileges->Present[4] = pPrivileges->Enabled[4] /*= pPrivileges->EnabledByDefault[4]*/ = 0x0f;

				PsDereferencePrimaryToken(pAccessToken);
			}

			if(pProcess != PsGetCurrentProcess())
				ObDereferenceObject(pProcess);
		}
	}
	else status = STATUS_NOT_SUPPORTED;

	return status;
}