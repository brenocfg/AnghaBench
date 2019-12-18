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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastErrorText (int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetSelectedProcessId () ; 
 int /*<<< orphan*/  IDS_MSG_CLOSESYSTEMPROCESS ; 
 int /*<<< orphan*/  IDS_MSG_TASKMGRWARNING ; 
 int /*<<< orphan*/  IDS_MSG_UNABLETERMINATEPRO ; 
 int /*<<< orphan*/  IDS_MSG_WARNINGTERMINATING ; 
 scalar_t__ IDYES ; 
 scalar_t__ IsCriticalProcess (scalar_t__) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MB_ICONSTOP ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int MB_TOPMOST ; 
 int MB_YESNO ; 
 scalar_t__ MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OpenProcess (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_TERMINATE ; 
 int /*<<< orphan*/  ShutdownProcessTree (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 

void ProcessPage_OnEndProcessTree(void)
{
    DWORD   dwProcessId;
    HANDLE  hProcess;
    WCHAR   szTitle[256];
    WCHAR   strErrorText[260];

    dwProcessId = GetSelectedProcessId();

    if (dwProcessId == 0)
        return;

    hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);

    /* forbid killing system processes even if we have privileges -- sigh, windows kludge! */
    if (hProcess && IsCriticalProcess(hProcess))
    {
        LoadStringW(hInst, IDS_MSG_UNABLETERMINATEPRO, szTitle, 256);
        LoadStringW(hInst, IDS_MSG_CLOSESYSTEMPROCESS, strErrorText, 256);
        MessageBoxW(hMainWnd, strErrorText, szTitle, MB_OK|MB_ICONWARNING|MB_TOPMOST);
        CloseHandle(hProcess);
        return;
    }

    LoadStringW(hInst, IDS_MSG_WARNINGTERMINATING, strErrorText, 256);
    LoadStringW(hInst, IDS_MSG_TASKMGRWARNING, szTitle, 256);
    if (MessageBoxW(hMainWnd, strErrorText, szTitle, MB_YESNO|MB_ICONWARNING) != IDYES)
    {
        if (hProcess) CloseHandle(hProcess);
        return;
    }

    if (!hProcess)
    {
        GetLastErrorText(strErrorText, 260);
        LoadStringW(hInst, IDS_MSG_UNABLETERMINATEPRO, szTitle, 256);
        MessageBoxW(hMainWnd, strErrorText, szTitle, MB_OK|MB_ICONSTOP);
        return;
    }

    if (!ShutdownProcessTree(hProcess, dwProcessId))
    {
        GetLastErrorText(strErrorText, 260);
        LoadStringW(hInst, IDS_MSG_UNABLETERMINATEPRO, szTitle, 256);
        MessageBoxW(hMainWnd, strErrorText, szTitle, MB_OK|MB_ICONSTOP);
    }

    CloseHandle(hProcess);
}