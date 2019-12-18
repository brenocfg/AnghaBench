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
 int /*<<< orphan*/ * MIMIKATZ_DEFAULT_LOG ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ kull_m_output_file (int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_standard_log(int argc, wchar_t * argv[])
{
	PCWCHAR filename = (kull_m_string_args_byName(argc, argv, L"stop", NULL, NULL) ? NULL : (argc ? argv[0] : MIMIKATZ_DEFAULT_LOG));
	kprintf(L"Using \'%s\' for logfile : %s\n", filename, kull_m_output_file(filename) ? L"OK" : L"KO");
	return STATUS_SUCCESS;
}