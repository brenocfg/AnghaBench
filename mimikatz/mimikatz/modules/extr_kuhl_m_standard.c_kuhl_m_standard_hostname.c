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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_net_getComputerName (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

NTSTATUS kuhl_m_standard_hostname(int argc, wchar_t * argv[])
{
	wchar_t *buffer;
	if(kull_m_net_getComputerName(TRUE, &buffer))
	{
		kprintf(L"%s", buffer);
		LocalFree(buffer);
	}
	if(kull_m_net_getComputerName(FALSE, &buffer))
	{
		kprintf(L" (%s)", buffer);
		LocalFree(buffer);
	}
	kprintf(L"\n");
	return STATUS_SUCCESS;
}