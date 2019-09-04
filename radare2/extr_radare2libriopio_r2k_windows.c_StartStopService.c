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
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 scalar_t__ ControlService (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DELETE ; 
 int /*<<< orphan*/  DeleteService (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenService (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SC_MANAGER_CREATE_SERVICE ; 
 int /*<<< orphan*/  SERVICE_CONTROL_STOP ; 
 int SERVICE_START ; 
 int SERVICE_STOP ; 
 scalar_t__ StartService (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eprintf (char*) ; 

BOOL StartStopService(LPCTSTR lpServiceName, BOOL bStop) {
	HANDLE hSCManager;
	HANDLE hService;
	SERVICE_STATUS ssStatus;
	BOOL ret = FALSE;
	hSCManager = OpenSCManager (NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (hSCManager)	{
		hService = OpenService (hSCManager, lpServiceName, SERVICE_START | DELETE | SERVICE_STOP);
		if (hService) {
			if (!bStop) {
				if (StartService (hService, 0, NULL)) {
					eprintf ("Service started [OK]\n");
					ret = TRUE;
				} else {
					eprintf ("Service started [FAIL]\n");
				}
			} else {
				if (ControlService (hService, SERVICE_CONTROL_STOP, &ssStatus)) {
					eprintf ("Service Stopped [OK]\n");
					ret = TRUE;
				} else {
					eprintf ("Service Stopped [FAIL]\n");
				}
			}
			CloseServiceHandle (hService);
			DeleteService (hService);
		}
		CloseServiceHandle (hSCManager);
	}
	return ret;
}