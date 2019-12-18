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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ ** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SERVICES_ACTIVE_DATABASE ; 
 int /*<<< orphan*/  SERVICE_START ; 
 int /*<<< orphan*/  StartServiceW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StdErr ; 

__attribute__((used)) static
INT
StartOneService(INT argc, WCHAR **argv)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    LPCWSTR *lpArgVectors = NULL;
    DWORD dwError = ERROR_SUCCESS;
    INT nError = 0;
    INT i;

    hManager = OpenSCManagerW(NULL,
                              SERVICES_ACTIVE_DATABASE,
                              SC_MANAGER_ENUMERATE_SERVICE);
    if (hManager == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    hService = OpenServiceW(hManager,
                            argv[2],
                            SERVICE_START);
    if (hService == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    lpArgVectors = HeapAlloc(GetProcessHeap(),
                             0,
                             (argc - 2) * sizeof(LPCWSTR));
    if (lpArgVectors == NULL)
    {
        dwError = GetLastError();
        nError = 1;
        goto done;
    }

    for (i = 2; i < argc; i++)
    {
        lpArgVectors[i - 2] = argv[i];
    }

    if (!StartServiceW(hService,
                       (DWORD)argc - 2,
                       lpArgVectors))
    {
        dwError = GetLastError();
        nError = 1;
    }

done:
    if (lpArgVectors != NULL)
        HeapFree(GetProcessHeap(), 0, (LPVOID)lpArgVectors);

    if (hService != NULL)
        CloseServiceHandle(hService);

    if (hManager != NULL)
        CloseServiceHandle(hManager);

    if (dwError != ERROR_SUCCESS)
    {
        /* FIXME: Print proper error message */
        ConPrintf(StdErr, L"Error: %lu\n", dwError);
    }

    return nError;
}