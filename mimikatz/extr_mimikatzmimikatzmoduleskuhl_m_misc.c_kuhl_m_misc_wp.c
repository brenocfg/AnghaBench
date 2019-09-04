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
struct TYPE_3__ {int /*<<< orphan*/  process; int /*<<< orphan*/ * wp; } ;
typedef  int /*<<< orphan*/ * PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ KIWI_WP_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_misc_wp_callback ; 
 int /*<<< orphan*/  kull_m_process_getProcessInformation (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,char*) ; 

NTSTATUS kuhl_m_misc_wp(int argc, wchar_t * argv[])
{
	KIWI_WP_DATA data;
	PCWCHAR process;
	if(kull_m_string_args_byName(argc, argv, L"file", &data.wp, NULL))
	{
		kull_m_string_args_byName(argc, argv, L"process", &process, L"explorer.exe");
		RtlInitUnicodeString(&data.process, process);
		kprintf(L"Wallpaper file: %s\n", data.wp);
		kprintf(L"Proxy process : %wZ\n", &data.process);
		kull_m_process_getProcessInformation(kuhl_m_misc_wp_callback, &data);
	}
	else PRINT_ERROR(L"file argument is needed\n");
	return STATUS_SUCCESS;
}