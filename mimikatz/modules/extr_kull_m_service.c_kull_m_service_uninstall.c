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
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SERVICE_NOT_ACTIVE ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_service_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_service_stop (int /*<<< orphan*/ ) ; 

BOOL kull_m_service_uninstall(PCWSTR serviceName)
{
	BOOL status = FALSE, toRemove = TRUE;
	if(kull_m_service_stop(serviceName))
		kprintf(L"[+] \'%s\' service stopped\n", serviceName);
	else if(GetLastError() == ERROR_SERVICE_NOT_ACTIVE)
		kprintf(L"[*] \'%s\' service not running\n", serviceName);
	else
	{
		toRemove = FALSE;
		PRINT_ERROR_AUTO(L"kull_m_service_stop");
	}

	if(toRemove)
	{
		if(status = kull_m_service_remove(serviceName))
			kprintf(L"[+] \'%s\' service removed\n", serviceName);
		else PRINT_ERROR_AUTO(L"kull_m_service_remove");
	}
	return STATUS_SUCCESS;
}