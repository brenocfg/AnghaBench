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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_MIMIDRV_PROCESS_FULLPRIV ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kull_m_kernel_mimidrv_simple_output (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_kernel_processPrivilege(int argc, wchar_t * argv[])
{
	PCWCHAR szPid;
	ULONG pid = 0;

	if(kull_m_string_args_byName(argc, argv, L"pid", &szPid, NULL))
		pid = wcstoul(szPid, NULL, 0);
	
	kull_m_kernel_mimidrv_simple_output(IOCTL_MIMIDRV_PROCESS_FULLPRIV, pid ? &pid : NULL, pid ? sizeof(ULONG) : 0);
	return STATUS_SUCCESS;
}