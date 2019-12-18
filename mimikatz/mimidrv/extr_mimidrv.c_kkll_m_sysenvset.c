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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_2__ {char* Name; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  ValueLength; scalar_t__ ValueOffset; int /*<<< orphan*/  VendorGuid; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  (* PZWSETSYSTEMENVIRONMENTVALUEEX ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PMIMIDRV_VARIABLE_NAME_AND_VALUE ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ MmGetSystemRoutineAddress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STATUS_NOT_FOUND ; 

NTSTATUS kkll_m_sysenvset(SIZE_T szBufferIn, PVOID bufferIn, PKIWI_BUFFER outBuffer)
{
	NTSTATUS status = STATUS_NOT_FOUND;
	UNICODE_STRING uZwSetSystemEnvironmentVariableEx, uVar;
	PZWSETSYSTEMENVIRONMENTVALUEEX ZwSetSystemEnvironmentValueEx;
	PMIMIDRV_VARIABLE_NAME_AND_VALUE vnv = (PMIMIDRV_VARIABLE_NAME_AND_VALUE) bufferIn;
	RtlInitUnicodeString(&uZwSetSystemEnvironmentVariableEx, L"ZwSetSystemEnvironmentValueEx");
	RtlInitUnicodeString(&uVar, vnv->Name);
	if(ZwSetSystemEnvironmentValueEx = (PZWSETSYSTEMENVIRONMENTVALUEEX) MmGetSystemRoutineAddress(&uZwSetSystemEnvironmentVariableEx))
		status = ZwSetSystemEnvironmentValueEx(&uVar, &vnv->VendorGuid, (PUCHAR) vnv + vnv->ValueOffset, vnv->ValueLength, vnv->Attributes);
	return status;
}