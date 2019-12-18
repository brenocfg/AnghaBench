#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LUID ;

/* Variables and functions */
 scalar_t__ LookupPrivilegeValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  kuhl_m_privilege_simple (int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_privilege_name(int argc, wchar_t * argv[])
{
	NTSTATUS status = STATUS_INVALID_PARAMETER;
	LUID luid;
	if(argc)
	{
		if(LookupPrivilegeValue(NULL, argv[0], &luid))
		{
			if(!luid.HighPart)
				status = kuhl_m_privilege_simple(luid.LowPart);
			else PRINT_ERROR(L"LUID high part is %u\n", luid.HighPart);
		}
		else PRINT_ERROR_AUTO(L"LookupPrivilegeValue");
	}
	else PRINT_ERROR(L"Missing \'name\'\n");
	return status;
}