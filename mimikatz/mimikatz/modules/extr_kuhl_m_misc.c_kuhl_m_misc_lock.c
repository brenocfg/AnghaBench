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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_misc_lock_callback ; 
 int /*<<< orphan*/  kull_m_process_getProcessInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char*) ; 

NTSTATUS kuhl_m_misc_lock(int argc, wchar_t * argv[])
{
	PCWCHAR process;
	UNICODE_STRING uProcess;
	kull_m_string_args_byName(argc, argv, L"process", &process, L"explorer.exe");
		RtlInitUnicodeString(&uProcess, process);
		kprintf(L"Proxy process : %wZ\n", &uProcess);
		kull_m_process_getProcessInformation(kuhl_m_misc_lock_callback, &uProcess);
	return STATUS_SUCCESS;
}