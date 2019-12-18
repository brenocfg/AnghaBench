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
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ SetCurrentDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_file_getCurrentDirectory (int /*<<< orphan*/ **) ; 

NTSTATUS kuhl_m_standard_cd(int argc, wchar_t * argv[])
{
	wchar_t * buffer;
	if(kull_m_file_getCurrentDirectory(&buffer))
	{
		if(argc)
			kprintf(L"Cur: ");
		kprintf(L"%s\n", buffer);
		LocalFree(buffer);
	}
	else PRINT_ERROR_AUTO(L"kull_m_file_getCurrentDirectory");

	if(argc)
	{
		if(SetCurrentDirectory(argv[0]))
		{
			if(kull_m_file_getCurrentDirectory(&buffer))
			{
				kprintf(L"New: %s\n", buffer);
				LocalFree(buffer);
			}
			else PRINT_ERROR_AUTO(L"kull_m_file_getCurrentDirectory");
		}
		else PRINT_ERROR_AUTO(L"SetCurrentDirectory");
	}
	return STATUS_SUCCESS;
}