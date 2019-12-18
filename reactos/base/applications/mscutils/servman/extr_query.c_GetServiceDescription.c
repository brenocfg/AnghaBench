#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ lpDescription; } ;
typedef  TYPE_1__ SERVICE_DESCRIPTIONW ;
typedef  TYPE_1__ SERVICE_DESCRIPTION ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GetError () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ QueryServiceConfig2W (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SERVICE_CONFIG_DESCRIPTION ; 
 int /*<<< orphan*/  SERVICE_QUERY_CONFIG ; 
 int /*<<< orphan*/  StringCchCopyW (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int wcslen (scalar_t__) ; 

LPWSTR
GetServiceDescription(LPWSTR lpServiceName)
{
    SC_HANDLE hSCManager = NULL;
    SC_HANDLE hSc = NULL;
    SERVICE_DESCRIPTIONW *pServiceDescription = NULL;
    LPWSTR lpDescription = NULL;
    DWORD BytesNeeded = 0;
    DWORD dwSize;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ENUMERATE_SERVICE);
    if (hSCManager == NULL)
    {
        GetError();
        return NULL;
    }

    hSc = OpenServiceW(hSCManager,
                       lpServiceName,
                       SERVICE_QUERY_CONFIG);
    if (hSc)
    {
        if (!QueryServiceConfig2W(hSc,
                                  SERVICE_CONFIG_DESCRIPTION,
                                  NULL,
                                  0,
                                  &BytesNeeded))
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                pServiceDescription = (SERVICE_DESCRIPTION *) HeapAlloc(ProcessHeap,
                                                                        0,
                                                                        BytesNeeded);
                if (pServiceDescription == NULL)
                    goto cleanup;

                if (QueryServiceConfig2W(hSc,
                                         SERVICE_CONFIG_DESCRIPTION,
                                         (LPBYTE)pServiceDescription,
                                         BytesNeeded,
                                         &BytesNeeded))
                {
                    if (pServiceDescription->lpDescription)
                    {
                        dwSize = wcslen(pServiceDescription->lpDescription) + 1;
                        lpDescription = HeapAlloc(ProcessHeap,
                                                  0,
                                                  dwSize * sizeof(WCHAR));
                        if (lpDescription)
                        {
                            StringCchCopyW(lpDescription,
                                           dwSize,
                                           pServiceDescription->lpDescription);
                        }
                    }
                }
            }
        }
    }

cleanup:
    if (pServiceDescription)
        HeapFree(ProcessHeap,
                 0,
                 pServiceDescription);
    if (hSCManager != NULL)
        CloseServiceHandle(hSCManager);
    if (hSc != NULL)
        CloseServiceHandle(hSc);

    return lpDescription;
}