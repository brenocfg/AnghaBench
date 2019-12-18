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
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kuhl_m_sr98_b0_descr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_sr98_b0(int argc, wchar_t * argv[])
{
	PCWCHAR szB0;
	if(argc)
	{
		if(!kull_m_string_args_byName(argc, argv, L"b0", &szB0, NULL))
			szB0 = argv[0];
		kuhl_m_sr98_b0_descr(wcstoul(szB0, NULL, 0));
	}
	else PRINT_ERROR(L"[/b0:]0x........ argument is needed\n");
	return STATUS_SUCCESS;
}