#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_4__ {size_t HandleCount; int /*<<< orphan*/ * Handles; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSYSTEM_HANDLE_INFORMATION ;
typedef  scalar_t__ (* PKULL_M_SYSTEM_HANDLE_ENUM_CALLBACK ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemHandleInformation ; 
 int /*<<< orphan*/  kull_m_process_NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 

NTSTATUS kull_m_handle_getHandles(PKULL_M_SYSTEM_HANDLE_ENUM_CALLBACK callBack, PVOID pvArg)
{
	NTSTATUS status;
	ULONG i;
	PSYSTEM_HANDLE_INFORMATION buffer = NULL;

	status = kull_m_process_NtQuerySystemInformation(SystemHandleInformation, &buffer, 0);
	if(NT_SUCCESS(status))
	{
		for(i = 0; (i < buffer->HandleCount) && callBack(&buffer->Handles[i], pvArg); i++);
		LocalFree(buffer);
	}
	return status;
}