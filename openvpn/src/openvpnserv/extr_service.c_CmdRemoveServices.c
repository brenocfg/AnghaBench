#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  display_name; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ openvpn_service_t ;
struct TYPE_7__ {scalar_t__ dwCurrentState; } ;
typedef  TYPE_2__ SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ControlService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int DELETE ; 
 scalar_t__ DeleteService (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastErrorText () ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ QueryServiceStatus (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_CONTROL_STOP ; 
 int SERVICE_QUERY_STATUS ; 
 int SERVICE_STOP ; 
 scalar_t__ SERVICE_STOPPED ; 
 scalar_t__ SERVICE_STOP_PENDING ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int _service_max ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 TYPE_1__* openvpn_service ; 

__attribute__((used)) static int
CmdRemoveServices()
{
    SC_HANDLE service;
    SC_HANDLE svc_ctl_mgr;
    SERVICE_STATUS status;
    int i, ret = _service_max;

    svc_ctl_mgr = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (svc_ctl_mgr == NULL)
    {
        _tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText());
        return 1;
    }

    for (i = 0; i < _service_max; i++)
    {
        openvpn_service_t *ovpn_svc = &openvpn_service[i];
        service = OpenService(svc_ctl_mgr, ovpn_svc->name,
                              DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);
        if (service == NULL)
        {
            _tprintf(TEXT("OpenService failed - %s\n"), GetLastErrorText());
            goto out;
        }

        /* try to stop the service */
        if (ControlService(service, SERVICE_CONTROL_STOP, &status))
        {
            _tprintf(TEXT("Stopping %s."), ovpn_svc->display_name);
            Sleep(1000);

            while (QueryServiceStatus(service, &status))
            {
                if (status.dwCurrentState == SERVICE_STOP_PENDING)
                {
                    _tprintf(TEXT("."));
                    Sleep(1000);
                }
                else
                {
                    break;
                }
            }

            if (status.dwCurrentState == SERVICE_STOPPED)
            {
                _tprintf(TEXT("\n%s stopped.\n"), ovpn_svc->display_name);
            }
            else
            {
                _tprintf(TEXT("\n%s failed to stop.\n"), ovpn_svc->display_name);
            }
        }

        /* now remove the service */
        if (DeleteService(service))
        {
            _tprintf(TEXT("%s removed.\n"), ovpn_svc->display_name);
            --ret;
        }
        else
        {
            _tprintf(TEXT("DeleteService failed - %s\n"), GetLastErrorText());
        }

        CloseServiceHandle(service);
    }

out:
    CloseServiceHandle(svc_ctl_mgr);
    return ret;
}