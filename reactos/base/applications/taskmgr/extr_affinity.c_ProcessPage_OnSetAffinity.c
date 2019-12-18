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
typedef  int /*<<< orphan*/  szTitle ;
typedef  int /*<<< orphan*/  strErrorText ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AffinityDialogWndProc ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DialogBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastErrorText (int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetSelectedProcessId () ; 
 int /*<<< orphan*/  IDD_AFFINITY_DIALOG ; 
 int /*<<< orphan*/  IDS_MSG_ACCESSPROCESSAFF ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int MB_ICONSTOP ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OpenProcess (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int PROCESS_QUERY_INFORMATION ; 
 int PROCESS_SET_INFORMATION ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/ * hProcessAffinityHandle ; 

void ProcessPage_OnSetAffinity(void)
{
    DWORD    dwProcessId;
    WCHAR    strErrorText[260];
    WCHAR    szTitle[256];

    dwProcessId = GetSelectedProcessId();

    if (dwProcessId == 0)
        return;

    hProcessAffinityHandle = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_SET_INFORMATION, FALSE, dwProcessId);
    if (!hProcessAffinityHandle) {
        GetLastErrorText(strErrorText, sizeof(strErrorText) / sizeof(WCHAR));
        LoadStringW(hInst, IDS_MSG_ACCESSPROCESSAFF, szTitle, sizeof(szTitle) / sizeof(WCHAR));
        MessageBoxW(hMainWnd, strErrorText, szTitle, MB_OK|MB_ICONSTOP);
        return;
    }
    DialogBoxW(hInst, MAKEINTRESOURCEW(IDD_AFFINITY_DIALOG), hMainWnd, AffinityDialogWndProc);
    if (hProcessAffinityHandle)    {
        CloseHandle(hProcessAffinityHandle);
        hProcessAffinityHandle = NULL;
    }
}