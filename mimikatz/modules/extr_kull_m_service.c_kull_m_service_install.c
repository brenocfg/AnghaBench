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
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SERVICE_ALREADY_RUNNING ; 
 scalar_t__ ERROR_SERVICE_DOES_NOT_EXIST ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int READ_CONTROL ; 
 int SC_MANAGER_CONNECT ; 
 int SC_MANAGER_CREATE_SERVICE ; 
 int /*<<< orphan*/  SERVICES_ACTIVE_DATABASE ; 
 int /*<<< orphan*/  SERVICE_ERROR_NORMAL ; 
 int SERVICE_START ; 
 scalar_t__ StartService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int WRITE_DAC ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_service_addWorldToSD (int /*<<< orphan*/ *) ; 

BOOL kull_m_service_install(PCWSTR serviceName, PCWSTR displayName, PCWSTR binPath, DWORD serviceType, DWORD startType, BOOL startIt)
{
	BOOL status = FALSE;
	SC_HANDLE hSC = NULL, hS = NULL;

	if(hSC = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE))
	{
		if(hS = OpenService(hSC, serviceName, SERVICE_START))
		{
			kprintf(L"[+] \'%s\' service already registered\n", serviceName);
		}
		else
		{
			if(GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST)
			{
				kprintf(L"[*] \'%s\' service not present\n", serviceName);
				if(hS = CreateService(hSC, serviceName, displayName, READ_CONTROL | WRITE_DAC | SERVICE_START, serviceType, startType, SERVICE_ERROR_NORMAL, binPath, NULL, NULL, NULL, NULL, NULL))
				{
					kprintf(L"[+] \'%s\' service successfully registered\n", serviceName);
					if(status = kull_m_service_addWorldToSD(hS))
						kprintf(L"[+] \'%s\' service ACL to everyone\n", serviceName);
					else PRINT_ERROR_AUTO(L"kull_m_service_addWorldToSD");
				}
				else PRINT_ERROR_AUTO(L"CreateService");
			}
			else PRINT_ERROR_AUTO(L"OpenService");
		}
		if(hS)
		{
			if(startIt)
			{
				if(status = StartService(hS, 0, NULL))
					kprintf(L"[+] \'%s\' service started\n", serviceName);
				else if(GetLastError() == ERROR_SERVICE_ALREADY_RUNNING)
					kprintf(L"[*] \'%s\' service already started\n", serviceName);
				else PRINT_ERROR_AUTO(L"StartService");
			}
			CloseServiceHandle(hS);
		}
		CloseServiceHandle(hSC);
	}
	else PRINT_ERROR_AUTO(L"OpenSCManager(create)");
	return status;
}