#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ hControlPipe; } ;
typedef  int /*<<< orphan*/  ServiceCurrent ;
typedef  TYPE_1__* PSERVICE_IMAGE ;
typedef  scalar_t__ HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CreateNamedPipeW (int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FILE_FLAG_OVERLAPPED ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int PIPE_ACCESS_DUPLEX ; 
 int PIPE_READMODE_MESSAGE ; 
 int PIPE_TYPE_MESSAGE ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  PipeTimeout ; 
 int /*<<< orphan*/  REG_DWORD ; 
 scalar_t__ REG_OPENED_EXISTING_KEY ; 
 int /*<<< orphan*/  REG_OPTION_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ RegQueryValueExW (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegSetValueExW (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StringCchPrintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static DWORD
ScmCreateNewControlPipe(PSERVICE_IMAGE pServiceImage)
{
    WCHAR szControlPipeName[MAX_PATH + 1];
    HKEY hServiceCurrentKey = INVALID_HANDLE_VALUE;
    DWORD ServiceCurrent = 0;
    DWORD KeyDisposition;
    DWORD dwKeySize;
    DWORD dwError;

    /* Get the service number */
    /* TODO: Create registry entry with correct write access */
    dwError = RegCreateKeyExW(HKEY_LOCAL_MACHINE,
                              L"SYSTEM\\CurrentControlSet\\Control\\ServiceCurrent", 0, NULL,
                              REG_OPTION_VOLATILE,
                              KEY_WRITE | KEY_READ,
                              NULL,
                              &hServiceCurrentKey,
                              &KeyDisposition);
    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("RegCreateKeyEx() failed with error %lu\n", dwError);
        return dwError;
    }

    if (KeyDisposition == REG_OPENED_EXISTING_KEY)
    {
        dwKeySize = sizeof(DWORD);
        dwError = RegQueryValueExW(hServiceCurrentKey,
                                   L"", 0, NULL, (BYTE*)&ServiceCurrent, &dwKeySize);

        if (dwError != ERROR_SUCCESS)
        {
            RegCloseKey(hServiceCurrentKey);
            DPRINT1("RegQueryValueEx() failed with error %lu\n", dwError);
            return dwError;
        }

        ServiceCurrent++;
    }

    dwError = RegSetValueExW(hServiceCurrentKey, L"", 0, REG_DWORD, (BYTE*)&ServiceCurrent, sizeof(ServiceCurrent));

    RegCloseKey(hServiceCurrentKey);

    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("RegSetValueExW() failed (Error %lu)\n", dwError);
        return dwError;
    }

    /* Create '\\.\pipe\net\NtControlPipeXXX' instance */
    StringCchPrintfW(szControlPipeName, ARRAYSIZE(szControlPipeName),
                     L"\\\\.\\pipe\\net\\NtControlPipe%lu", ServiceCurrent);

    DPRINT("PipeName: %S\n", szControlPipeName);

    pServiceImage->hControlPipe = CreateNamedPipeW(szControlPipeName,
                                                   PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
                                                   PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                                                   100,
                                                   8000,
                                                   4,
                                                   PipeTimeout,
                                                   NULL);
    DPRINT("CreateNamedPipeW(%S) done\n", szControlPipeName);
    if (pServiceImage->hControlPipe == INVALID_HANDLE_VALUE)
    {
        DPRINT1("Failed to create control pipe!\n");
        return GetLastError();
    }

    return ERROR_SUCCESS;
}