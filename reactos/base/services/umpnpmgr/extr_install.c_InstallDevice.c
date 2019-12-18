#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  Value ;
struct TYPE_10__ {char* Data1; int /*<<< orphan*/ * Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; } ;
typedef  TYPE_1__ UUID ;
struct TYPE_11__ {int cb; scalar_t__ hProcess; scalar_t__ hThread; } ;
typedef  int /*<<< orphan*/  StartupInfo ;
typedef  int /*<<< orphan*/  ShowWizard ;
typedef  TYPE_2__ STARTUPINFOW ;
typedef  int /*<<< orphan*/  ProcessInfo ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int* PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  InstallEventName ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CONFIGFLAG_FAILEDINSTALL ; 
 int /*<<< orphan*/  CREATE_UNICODE_ENVIRONMENT ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConnectNamedPipe (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateEnvironmentBlock (int /*<<< orphan*/ **,scalar_t__,int) ; 
 scalar_t__ CreateEventW (int /*<<< orphan*/ *,int,int,int*) ; 
 scalar_t__ CreateNamedPipeW (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessAsUserW (scalar_t__,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DPRINT (char*,int*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int*,...) ; 
 int /*<<< orphan*/  DestroyEnvironmentBlock (int /*<<< orphan*/ *) ; 
 int* ERROR_PIPE_CONNECTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int* GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  PIPE_ACCESS_OUTBOUND ; 
 int /*<<< orphan*/  PIPE_TYPE_BYTE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int TRUE ; 
 int /*<<< orphan*/  UuidCreate (TYPE_1__*) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hEnumKey ; 
 scalar_t__ hUserToken ; 
 int /*<<< orphan*/  swprintf (int*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscat (int*,int*) ; 
 int /*<<< orphan*/  wcscpy (int*,char*) ; 
 int wcslen (int*) ; 

__attribute__((used)) static BOOL
InstallDevice(PCWSTR DeviceInstance, BOOL ShowWizard)
{
    BOOL DeviceInstalled = FALSE;
    DWORD BytesWritten;
    DWORD Value;
    HANDLE hInstallEvent;
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    LPVOID Environment = NULL;
    PROCESS_INFORMATION ProcessInfo;
    STARTUPINFOW StartupInfo;
    UUID RandomUuid;
    HKEY DeviceKey;

    /* The following lengths are constant (see below), they cannot overflow */
    WCHAR CommandLine[116];
    WCHAR InstallEventName[73];
    WCHAR PipeName[74];
    WCHAR UuidString[39];

    DPRINT("InstallDevice(%S, %d)\n", DeviceInstance, ShowWizard);

    ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));

    if (RegOpenKeyExW(hEnumKey,
                      DeviceInstance,
                      0,
                      KEY_QUERY_VALUE,
                      &DeviceKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueExW(DeviceKey,
                             L"Class",
                             NULL,
                             NULL,
                             NULL,
                             NULL) == ERROR_SUCCESS)
        {
            DPRINT("No need to install: %S\n", DeviceInstance);
            RegCloseKey(DeviceKey);
            return TRUE;
        }

        BytesWritten = sizeof(DWORD);
        if (RegQueryValueExW(DeviceKey,
                             L"ConfigFlags",
                             NULL,
                             NULL,
                             (PBYTE)&Value,
                             &BytesWritten) == ERROR_SUCCESS)
        {
            if (Value & CONFIGFLAG_FAILEDINSTALL)
            {
                DPRINT("No need to install: %S\n", DeviceInstance);
                RegCloseKey(DeviceKey);
                return TRUE;
            }
        }

        RegCloseKey(DeviceKey);
    }

    DPRINT1("Installing: %S\n", DeviceInstance);

    /* Create a random UUID for the named pipe & event*/
    UuidCreate(&RandomUuid);
    swprintf(UuidString, L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
        RandomUuid.Data1, RandomUuid.Data2, RandomUuid.Data3,
        RandomUuid.Data4[0], RandomUuid.Data4[1], RandomUuid.Data4[2],
        RandomUuid.Data4[3], RandomUuid.Data4[4], RandomUuid.Data4[5],
        RandomUuid.Data4[6], RandomUuid.Data4[7]);

    /* Create the event */
    wcscpy(InstallEventName, L"Global\\PNP_Device_Install_Event_0.");
    wcscat(InstallEventName, UuidString);
    hInstallEvent = CreateEventW(NULL, TRUE, FALSE, InstallEventName);
    if (!hInstallEvent)
    {
        DPRINT1("CreateEventW('%ls') failed with error %lu\n", InstallEventName, GetLastError());
        goto cleanup;
    }

    /* Create the named pipe */
    wcscpy(PipeName, L"\\\\.\\pipe\\PNP_Device_Install_Pipe_0.");
    wcscat(PipeName, UuidString);
    hPipe = CreateNamedPipeW(PipeName, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 512, 512, 0, NULL);
    if (hPipe == INVALID_HANDLE_VALUE)
    {
        DPRINT1("CreateNamedPipeW failed with error %u\n", GetLastError());
        goto cleanup;
    }

    /* Launch rundll32 to call ClientSideInstallW */
    wcscpy(CommandLine, L"rundll32.exe newdev.dll,ClientSideInstall ");
    wcscat(CommandLine, PipeName);

    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof(StartupInfo);

    if (hUserToken)
    {
        /* newdev has to run under the environment of the current user */
        if (!CreateEnvironmentBlock(&Environment, hUserToken, FALSE))
        {
            DPRINT1("CreateEnvironmentBlock failed with error %d\n", GetLastError());
            goto cleanup;
        }

        if (!CreateProcessAsUserW(hUserToken, NULL, CommandLine, NULL, NULL, FALSE, CREATE_UNICODE_ENVIRONMENT, Environment, NULL, &StartupInfo, &ProcessInfo))
        {
            DPRINT1("CreateProcessAsUserW failed with error %u\n", GetLastError());
            goto cleanup;
        }
    }
    else
    {
        /* FIXME: This is probably not correct, I guess newdev should never be run with SYSTEM privileges.

           Still, we currently do that in 2nd stage setup and probably Console mode as well, so allow it here.
           (ShowWizard is only set to FALSE for these two modes) */
        ASSERT(!ShowWizard);

        if (!CreateProcessW(NULL, CommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
        {
            DPRINT1("CreateProcessW failed with error %u\n", GetLastError());
            goto cleanup;
        }
    }

    /* Wait for the function to connect to our pipe */
    if (!ConnectNamedPipe(hPipe, NULL))
    {
        if (GetLastError() != ERROR_PIPE_CONNECTED)
        {
            DPRINT1("ConnectNamedPipe failed with error %u\n", GetLastError());
            goto cleanup;
        }
    }

    /* Pass the data. The following output is partly compatible to Windows XP SP2 (researched using a modified newdev.dll to log this stuff) */
    Value = sizeof(InstallEventName);
    WriteFile(hPipe, &Value, sizeof(Value), &BytesWritten, NULL);
    WriteFile(hPipe, InstallEventName, Value, &BytesWritten, NULL);

    /* I couldn't figure out what the following value means under WinXP. It's usually 0 in my tests, but was also 5 once.
       Therefore the following line is entirely ReactOS-specific. We use the value here to pass the ShowWizard variable. */
    WriteFile(hPipe, &ShowWizard, sizeof(ShowWizard), &BytesWritten, NULL);

    Value = (wcslen(DeviceInstance) + 1) * sizeof(WCHAR);
    WriteFile(hPipe, &Value, sizeof(Value), &BytesWritten, NULL);
    WriteFile(hPipe, DeviceInstance, Value, &BytesWritten, NULL);

    /* Wait for newdev.dll to finish processing */
    WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

    /* If the event got signalled, this is success */
    DeviceInstalled = WaitForSingleObject(hInstallEvent, 0) == WAIT_OBJECT_0;

cleanup:
    if (hInstallEvent)
        CloseHandle(hInstallEvent);

    if (hPipe != INVALID_HANDLE_VALUE)
        CloseHandle(hPipe);

    if (Environment)
        DestroyEnvironmentBlock(Environment);

    if (ProcessInfo.hProcess)
        CloseHandle(ProcessInfo.hProcess);

    if (ProcessInfo.hThread)
        CloseHandle(ProcessInfo.hThread);

    if (!DeviceInstalled)
    {
        DPRINT1("InstallDevice failed for DeviceInstance '%ws'\n", DeviceInstance);
    }

    return DeviceInstalled;
}