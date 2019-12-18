#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_5__ {scalar_t__ ImageBase; } ;
struct TYPE_7__ {scalar_t__ ImageSize; TYPE_1__ BasicInfo; scalar_t__ FileNameOffset; scalar_t__ FullPathName; } ;
struct TYPE_6__ {scalar_t__ addr; int /*<<< orphan*/  isFound; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_2__* PKKLL_M_MODULE_FROM_ADDR ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  TYPE_3__* PAUX_MODULE_EXTENDED_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

NTSTATUS kkll_m_modules_fromAddr_callback(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PAUX_MODULE_EXTENDED_INFO pModule, PVOID pvArg, BOOLEAN * mustContinue)
{
	NTSTATUS status = STATUS_SUCCESS;
	PKKLL_M_MODULE_FROM_ADDR pStructAddr = (PKKLL_M_MODULE_FROM_ADDR) pvArg;

	if((pStructAddr->addr >= (ULONG_PTR) pModule->BasicInfo.ImageBase) && (pStructAddr->addr < ((ULONG_PTR) pModule->BasicInfo.ImageBase + pModule->ImageSize)))
	{
		*mustContinue = FALSE;
		pStructAddr->isFound = TRUE;
		status = kprintf(outBuffer, L"0x%p [%S + 0x%x]\n", (PVOID) pStructAddr->addr, pModule->FullPathName + pModule->FileNameOffset, pStructAddr->addr - (ULONG_PTR) pModule->BasicInfo.ImageBase);
	}
	return status;
}