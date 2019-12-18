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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dwCrashDumpEnabled; scalar_t__ szDumpFile; scalar_t__ szMinidumpDir; } ;
typedef  TYPE_1__* PSTARTINFO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_STRRECDEBUGCOMBO ; 
 int /*<<< orphan*/  IDC_STRRECDUMPFILE ; 
 int /*<<< orphan*/  IDC_STRRECOVERWRITE ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETTEXT ; 

__attribute__((used)) static VOID
SetCrashDlgItems(HWND hwnd, PSTARTINFO pStartInfo)
{
    if (pStartInfo->dwCrashDumpEnabled == 0)
    {
        /* No crash information required */
        EnableWindow(GetDlgItem(hwnd, IDC_STRRECDUMPFILE), FALSE);
        EnableWindow(GetDlgItem(hwnd, IDC_STRRECOVERWRITE), FALSE);
    }
    else if (pStartInfo->dwCrashDumpEnabled == 3)
    {
        /* Minidump type */
        EnableWindow(GetDlgItem(hwnd, IDC_STRRECDUMPFILE), TRUE);
        EnableWindow(GetDlgItem(hwnd, IDC_STRRECOVERWRITE), FALSE);
        SendMessageW(GetDlgItem(hwnd, IDC_STRRECDUMPFILE), WM_SETTEXT, (WPARAM)0, (LPARAM)pStartInfo->szMinidumpDir);
    }
    else if (pStartInfo->dwCrashDumpEnabled == 1 || pStartInfo->dwCrashDumpEnabled == 2)
    {
        /* Kernel or complete dump */
        EnableWindow(GetDlgItem(hwnd, IDC_STRRECDUMPFILE), TRUE);
        EnableWindow(GetDlgItem(hwnd, IDC_STRRECOVERWRITE), TRUE);
        SendMessageW(GetDlgItem(hwnd, IDC_STRRECDUMPFILE), WM_SETTEXT, (WPARAM)0, (LPARAM)pStartInfo->szDumpFile);
    }
    SendDlgItemMessageW(hwnd, IDC_STRRECDEBUGCOMBO, CB_SETCURSEL, (WPARAM)pStartInfo->dwCrashDumpEnabled, (LPARAM)0);
}