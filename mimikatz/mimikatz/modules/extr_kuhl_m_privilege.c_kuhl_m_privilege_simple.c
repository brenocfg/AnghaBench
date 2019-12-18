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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlAdjustPrivilege (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_privilege_simple(ULONG privId)
{
	ULONG previousState;
	NTSTATUS status = RtlAdjustPrivilege(privId, TRUE, FALSE, &previousState);
	if(NT_SUCCESS(status))
		kprintf(L"Privilege \'%u\' OK\n", privId);
	else PRINT_ERROR(L"RtlAdjustPrivilege (%u) %08x\n", privId, status);
	return status;
}