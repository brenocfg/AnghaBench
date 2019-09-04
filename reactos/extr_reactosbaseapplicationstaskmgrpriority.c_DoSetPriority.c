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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastErrorText (int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetSelectedProcessId () ; 
 int /*<<< orphan*/  IDS_MSG_TASKMGRWARNING ; 
 int /*<<< orphan*/  IDS_MSG_UNABLECHANGEPRIORITY ; 
 int /*<<< orphan*/  IDS_MSG_WARNINGCHANGEPRIORITY ; 
 scalar_t__ IDYES ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MB_ICONSTOP ; 
 int MB_ICONWARNING ; 
 int MB_OK ; 
 int MB_YESNO ; 
 scalar_t__ MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PROCESS_SET_INFORMATION ; 
 int /*<<< orphan*/  SetPriorityClass (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 

void DoSetPriority(DWORD priority)
{
    DWORD   dwProcessId;
    HANDLE  hProcess;
    WCHAR   szText[260];
    WCHAR   szTitle[256];

    dwProcessId = GetSelectedProcessId();

    if (dwProcessId == 0)
        return;

    LoadStringW(hInst, IDS_MSG_TASKMGRWARNING, szTitle, 256);
    LoadStringW(hInst, IDS_MSG_WARNINGCHANGEPRIORITY, szText, 260);
    if (MessageBoxW(hMainWnd, szText, szTitle, MB_YESNO|MB_ICONWARNING) != IDYES)
        return;

    hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, dwProcessId);

    if (!hProcess)
    {
        GetLastErrorText(szText, 260);
        LoadStringW(hInst, IDS_MSG_UNABLECHANGEPRIORITY, szTitle, 256);
        MessageBoxW(hMainWnd, szText, szTitle, MB_OK|MB_ICONSTOP);
        return;
    }

    if (!SetPriorityClass(hProcess, priority))
    {
        GetLastErrorText(szText, 260);
        LoadStringW(hInst, IDS_MSG_UNABLECHANGEPRIORITY, szTitle, 256);
        MessageBoxW(hMainWnd, szText, szTitle, MB_OK|MB_ICONSTOP);
    }

    CloseHandle(hProcess);
}