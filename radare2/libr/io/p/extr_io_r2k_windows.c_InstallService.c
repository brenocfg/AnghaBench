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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (scalar_t__) ; 
 scalar_t__ CreateService (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DELETE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CREATE_SERVICE ; 
 int /*<<< orphan*/  SERVICE_DEMAND_START ; 
 int /*<<< orphan*/  SERVICE_ERROR_IGNORE ; 
 int /*<<< orphan*/  SERVICE_KERNEL_DRIVER ; 
 int SERVICE_START ; 
 int SERVICE_STOP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_conv_utf8_to_win (char const*) ; 

__attribute__((used)) static BOOL InstallService(const char * rutaDriver, LPCTSTR  lpServiceName, LPCTSTR  lpDisplayName) {
	HANDLE hService;
	BOOL ret = FALSE;
	HANDLE hSCManager = OpenSCManager (NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (hSCManager)	{
		LPTSTR rutaDriver_ = r_sys_conv_utf8_to_win (rutaDriver);
		hService = CreateService (hSCManager, lpServiceName, lpDisplayName, SERVICE_START | DELETE | SERVICE_STOP, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, rutaDriver_, NULL, NULL, NULL, NULL, NULL);
		if (hService) {
			CloseServiceHandle (hService);
			ret = TRUE;
		}
		free (rutaDriver_);
		CloseServiceHandle (hSCManager);
	}
	return ret;
}