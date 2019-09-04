#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dwCurrentState; } ;
struct TYPE_6__ {int /*<<< orphan*/  lpServiceName; TYPE_1__ ServiceStatus; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_2__* LPENUM_SERVICE_STATUS ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddServiceToList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SERVICE_STOPPED ; 
 scalar_t__ SERVICE_STOP_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* TV2_GetDependants (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static BOOL
BuildListOfServicesToStop(LPWSTR *lpServiceList,
                          LPWSTR lpServiceName)
{
    LPENUM_SERVICE_STATUS lpServiceStatus;
    DWORD dwCount, i;
    BOOL bRet = FALSE;

    /* Get a list of service dependents */
    lpServiceStatus = TV2_GetDependants(lpServiceName, &dwCount);
    if (lpServiceStatus)
    {
        for (i = 0; i < dwCount; i++)
        {
            /* Does this service need stopping? */
            if (lpServiceStatus[i].ServiceStatus.dwCurrentState != SERVICE_STOPPED &&
                lpServiceStatus[i].ServiceStatus.dwCurrentState != SERVICE_STOP_PENDING)
            {
                /* Add the service to the list */
                *lpServiceList = AddServiceToList(lpServiceList, lpServiceStatus[i].lpServiceName);

                /* We've got one */
                bRet = TRUE;
            }
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpServiceStatus);
    }

    return bRet;
}