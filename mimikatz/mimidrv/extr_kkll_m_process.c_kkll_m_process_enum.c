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
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  (* PKKLL_M_PROCESS_CALLBACK ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  scalar_t__ PEPROCESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__** EPROCESS_OffSetTable ; 
 size_t EprocessNext ; 
 size_t KiwiOsIndex ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ PsInitialSystemProcess ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS kkll_m_process_enum(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PKKLL_M_PROCESS_CALLBACK callback, PVOID pvArg)
{
	NTSTATUS status = STATUS_SUCCESS;
	PEPROCESS pProcess = NULL;
	for(
		pProcess = PsInitialSystemProcess;
		NT_SUCCESS(status) && (PEPROCESS) ((ULONG_PTR) (*(PVOID *) (((ULONG_PTR) pProcess) + EPROCESS_OffSetTable[KiwiOsIndex][EprocessNext])) - EPROCESS_OffSetTable[KiwiOsIndex][EprocessNext]) != PsInitialSystemProcess;
		pProcess = (PEPROCESS) ((ULONG_PTR) (*(PVOID *) (((ULONG_PTR) pProcess) + EPROCESS_OffSetTable[KiwiOsIndex][EprocessNext])) - EPROCESS_OffSetTable[KiwiOsIndex][EprocessNext])
		)
	{
		status = callback(szBufferIn, bufferIn, outBuffer, pProcess, pvArg);
	}
	return status;
}