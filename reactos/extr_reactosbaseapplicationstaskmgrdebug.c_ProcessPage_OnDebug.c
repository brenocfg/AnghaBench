#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strDebugger ;
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  pi ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int cb; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastErrorText (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetSelectedProcessId () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  IDS_MSG_TASKMGRWARNING ; 
 int /*<<< orphan*/  IDS_MSG_UNABLEDEBUGPROCESS ; 
 int /*<<< orphan*/  IDS_MSG_WARNINGDEBUG ; 
 scalar_t__ IDYES ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MB_ICONSTOP ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int MB_YESNO ; 
 scalar_t__ MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void ProcessPage_OnDebug(void)
{
    DWORD                dwProcessId;
    WCHAR                strErrorText[260];
    HKEY                 hKey;
    WCHAR                strDebugPath[260];
    WCHAR                strDebugger[260];
    DWORD                dwDebuggerSize;
    PROCESS_INFORMATION  pi;
    STARTUPINFOW         si;
    HANDLE               hDebugEvent;
    WCHAR                szTemp[256];
    WCHAR                szTempA[256];

    dwProcessId = GetSelectedProcessId();

    if (dwProcessId == 0)
        return;

    LoadStringW(hInst, IDS_MSG_WARNINGDEBUG, szTemp, ARRAYSIZE(szTemp));
    LoadStringW(hInst, IDS_MSG_TASKMGRWARNING, szTempA, ARRAYSIZE(szTempA));

    if (MessageBoxW(hMainWnd, szTemp, szTempA, MB_YESNO | MB_ICONWARNING) != IDYES)
    {
        GetLastErrorText(strErrorText, ARRAYSIZE(strErrorText));
        LoadStringW(hInst, IDS_MSG_UNABLEDEBUGPROCESS, szTemp, ARRAYSIZE(szTemp));
        MessageBoxW(hMainWnd, strErrorText, szTemp, MB_OK | MB_ICONSTOP);
        return;
    }

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug", 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
    {
        GetLastErrorText(strErrorText, ARRAYSIZE(strErrorText));
        LoadStringW(hInst, IDS_MSG_UNABLEDEBUGPROCESS, szTemp, ARRAYSIZE(szTemp));
        MessageBoxW(hMainWnd, strErrorText, szTemp, MB_OK | MB_ICONSTOP);
        return;
    }

    dwDebuggerSize = sizeof(strDebugger);
    if (RegQueryValueExW(hKey, L"Debugger", NULL, NULL, (LPBYTE)strDebugger, &dwDebuggerSize) != ERROR_SUCCESS)
    {
        GetLastErrorText(strErrorText, ARRAYSIZE(strErrorText));
        LoadStringW(hInst, IDS_MSG_UNABLEDEBUGPROCESS, szTemp, ARRAYSIZE(szTemp));
        MessageBoxW(hMainWnd, strErrorText, szTemp, MB_OK | MB_ICONSTOP);
        RegCloseKey(hKey);
        return;
    }

    RegCloseKey(hKey);

    hDebugEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
    if (!hDebugEvent)
    {
        GetLastErrorText(strErrorText, ARRAYSIZE(strErrorText));
        LoadStringW(hInst, IDS_MSG_UNABLEDEBUGPROCESS, szTemp, ARRAYSIZE(szTemp));
        MessageBoxW(hMainWnd, strErrorText, szTemp, MB_OK | MB_ICONSTOP);
        return;
    }

    wsprintfW(strDebugPath, strDebugger, dwProcessId, hDebugEvent);

    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    if (!CreateProcessW(NULL, strDebugPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        GetLastErrorText(strErrorText, ARRAYSIZE(strErrorText));
        LoadStringW(hInst, IDS_MSG_UNABLEDEBUGPROCESS, szTemp, ARRAYSIZE(szTemp));
        MessageBoxW(hMainWnd, strErrorText, szTemp, MB_OK | MB_ICONSTOP);
    }
    else
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }

    CloseHandle(hDebugEvent);
}