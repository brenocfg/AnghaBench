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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  (* PKKLL_M_MODULE_CALLBACK ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/ * PAUX_MODULE_EXTENDED_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  AUX_MODULE_EXTENDED_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AuxKlibQueryModuleInformation (int*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POOL_TAG ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 

NTSTATUS kkll_m_modules_enum(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer, PKKLL_M_MODULE_CALLBACK callback, PVOID pvArg)
{
	NTSTATUS status = STATUS_SUCCESS;
	ULONG i, modulesSize, numberOfModules;
	PAUX_MODULE_EXTENDED_INFO pModules;
	BOOLEAN mustContinue = TRUE;

	status = AuxKlibQueryModuleInformation(&modulesSize, sizeof(AUX_MODULE_EXTENDED_INFO), NULL);		
	if(NT_SUCCESS(status) && modulesSize)
	{
		if(pModules = (PAUX_MODULE_EXTENDED_INFO) ExAllocatePoolWithTag(PagedPool, modulesSize, POOL_TAG))
		{
			numberOfModules = modulesSize / sizeof(AUX_MODULE_EXTENDED_INFO);
			status = AuxKlibQueryModuleInformation(&modulesSize, sizeof(AUX_MODULE_EXTENDED_INFO), pModules);
			for(i = 0; NT_SUCCESS(status) && mustContinue && (i < numberOfModules); i++)
				status = callback(szBufferIn, bufferIn, outBuffer, pModules + i, pvArg, &mustContinue);	
			ExFreePoolWithTag(pModules, POOL_TAG);
		}
	}
	return status;	
}