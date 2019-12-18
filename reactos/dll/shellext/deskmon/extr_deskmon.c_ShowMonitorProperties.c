#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {TYPE_2__* SelMonitor; int /*<<< orphan*/  hwndDlg; } ;
struct TYPE_5__ {int /*<<< orphan*/  DeviceID; } ;
struct TYPE_6__ {TYPE_1__ dd; } ;
typedef  int /*<<< orphan*/  (* PDEVICEPROPERTIES ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_3__* PDESKMONITOR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/  HLOCAL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FUNC_DEVICEPROPERTIES ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetMonitorDevInstID (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char*) ; 

__attribute__((used)) static VOID
ShowMonitorProperties(PDESKMONITOR This)
{
    HMODULE hDevMgr;
    PDEVICEPROPERTIES pDeviceProperties;
    LPTSTR lpDevInstID;

    if (This->SelMonitor != NULL)
    {
        lpDevInstID = GetMonitorDevInstID(This->SelMonitor->dd.DeviceID);
        if (lpDevInstID != NULL)
        {
            hDevMgr = LoadLibrary(TEXT("devmgr.dll"));
            if (hDevMgr != NULL)
            {
                pDeviceProperties = (PDEVICEPROPERTIES)GetProcAddress(hDevMgr,
                                                                      FUNC_DEVICEPROPERTIES);
                if (pDeviceProperties != NULL)
                {
                    pDeviceProperties(This->hwndDlg,
                                       NULL,
                                       This->SelMonitor->dd.DeviceID,
                                       FALSE);
                }

                FreeLibrary(hDevMgr);
            }

            LocalFree((HLOCAL)lpDevInstID);
        }
    }
}