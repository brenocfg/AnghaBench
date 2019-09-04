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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 int DELETE ; 
 int /*<<< orphan*/  DeleteService (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OpenService (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SC_MANAGER_CREATE_SERVICE ; 
 int SERVICE_START ; 
 int SERVICE_STOP ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL RemoveService(LPCTSTR lpServiceName) {
	HANDLE hService;
	BOOL ret = FALSE;
	HANDLE hSCManager = OpenSCManager (NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (hSCManager) {
		hService = OpenService (hSCManager, lpServiceName, SERVICE_START | DELETE | SERVICE_STOP);
		if (hService) {
			DeleteService (hService);
			CloseServiceHandle (hService);
			ret = TRUE;
		}
		CloseServiceHandle (hSCManager);
	}
	return ret;
}