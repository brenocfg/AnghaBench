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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  kuhl_m_privilege_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_privilege_id(int argc, wchar_t * argv[])
{
	NTSTATUS status = STATUS_INVALID_PARAMETER;
	if(argc)
		status = kuhl_m_privilege_simple(wcstoul(argv[0], NULL, 0));
	else PRINT_ERROR(L"Missing \'id\'\n");
	return status;
}