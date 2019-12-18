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
typedef  scalar_t__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  SAMPR_HANDLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SamFreeMemory (scalar_t__*) ; 
 int /*<<< orphan*/  SamLookupIdsInDomain (int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__**,scalar_t__**) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_token_getSidNameUse (int /*<<< orphan*/ ) ; 

void kuhl_m_net_simpleLookup(SAMPR_HANDLE hDomainHandle, DWORD rid)
{
	NTSTATUS status;
	UNICODE_STRING *name;
	DWORD *usage;

	status = SamLookupIdsInDomain(hDomainHandle, 1, &rid, &name, &usage);
	if(NT_SUCCESS(status))
	{
		kprintf(L"%wZ\t(%s)", name, kull_m_token_getSidNameUse((SID_NAME_USE) *usage));
		SamFreeMemory(name);
		SamFreeMemory(usage);
	}
	else PRINT_ERROR(L"SamLookupIdsInDomain %08x", status);
}