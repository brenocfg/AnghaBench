#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_9__ {int cb; int /*<<< orphan*/ * hProcess; int /*<<< orphan*/ * hThread; } ;
struct TYPE_10__ {size_t Selection; TYPE_2__ PrevWindowPi; TYPE_1__* ScreenSaverItems; } ;
struct TYPE_8__ {int /*<<< orphan*/  szFilename; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__ STARTUPINFO ;
typedef  TYPE_3__* PDATA ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SCREENS_PREVIEW ; 
 int /*<<< orphan*/  TerminateProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
SetScreenSaverPreviewBox(HWND hwndDlg, PDATA pData)
{
    HWND hPreview = GetDlgItem(hwndDlg, IDC_SCREENS_PREVIEW);
    STARTUPINFO si;
    TCHAR szCmdline[2048];

    /* Kill off the previous preview process */
    if (pData->PrevWindowPi.hProcess)
    {
        TerminateProcess(pData->PrevWindowPi.hProcess, 0);
        CloseHandle(pData->PrevWindowPi.hProcess);
        CloseHandle(pData->PrevWindowPi.hThread);
        pData->PrevWindowPi.hThread = pData->PrevWindowPi.hProcess = NULL;
    }

    if (pData->Selection > 0)
    {
        _stprintf(szCmdline,
                  _T("%s /p %Iu"),
                  pData->ScreenSaverItems[pData->Selection].szFilename,
                  (ULONG_PTR)hPreview);

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pData->PrevWindowPi, sizeof(pData->PrevWindowPi));

        if (!CreateProcess(NULL,
                           szCmdline,
                           NULL,
                           NULL,
                           FALSE,
                           0,
                           NULL,
                           NULL,
                           &si,
                           &pData->PrevWindowPi))
        {
            pData->PrevWindowPi.hThread = pData->PrevWindowPi.hProcess = NULL;
        }
    }
}