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
typedef  size_t USHORT ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_2__ {size_t TableSize; int* OffsetToService; scalar_t__* ServiceTable; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int EX_FAST_REF_MASK ; 
 TYPE_1__* KeServiceDescriptorTable ; 
 scalar_t__ KiwiOsIndex ; 
 scalar_t__ KiwiOsIndex_VISTA ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kkll_m_modules_fromAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kkll_m_ssdt_getKeServiceDescriptorTable () ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,...) ; 

NTSTATUS kkll_m_ssdt_list(PKIWI_BUFFER outBuffer)
{
	NTSTATUS status;
	USHORT idxFunction;
	ULONG_PTR funcAddr;

#if defined(_M_X64)
	status = kkll_m_ssdt_getKeServiceDescriptorTable();
	if(NT_SUCCESS(status))
	{
#endif
		status = kprintf(outBuffer, L"KeServiceDescriptorTable : 0x%p (%u)\n", KeServiceDescriptorTable, KeServiceDescriptorTable->TableSize);
		for(idxFunction = 0; (idxFunction < KeServiceDescriptorTable->TableSize) && NT_SUCCESS(status) ; idxFunction++)
		{
#if defined(_M_IX86)
			funcAddr = (ULONG_PTR) KeServiceDescriptorTable->ServiceTable[idxFunction];
#else
			funcAddr = (ULONG_PTR) KeServiceDescriptorTable->OffsetToService;
			if(KiwiOsIndex < KiwiOsIndex_VISTA)
				funcAddr += KeServiceDescriptorTable->OffsetToService[idxFunction] & ~EX_FAST_REF_MASK;
			else
				funcAddr += KeServiceDescriptorTable->OffsetToService[idxFunction] >> 4;
#endif
			status = kprintf(outBuffer, L"[%5u] ", idxFunction);
			if(NT_SUCCESS(status))
				status = kkll_m_modules_fromAddr(outBuffer, (PVOID) funcAddr);
		}
#if defined(_M_X64)
	}
#endif
	return status;
}