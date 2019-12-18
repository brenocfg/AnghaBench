#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {TYPE_2__* pServiceFailure; } ;
struct TYPE_6__ {int dwResetPeriod; int* lpCommand; TYPE_1__* lpsaActions; int /*<<< orphan*/  cActions; } ;
struct TYPE_5__ {int Type; int Delay; } ;
typedef  int* PWSTR ;
typedef  TYPE_3__* PRECOVERYDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ LONG_PTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETCHECK ; 
 int BST_CHECKED ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 int IDC_ADD_FAILCOUNT ; 
 int IDC_FIRST_FAILURE ; 
 int IDC_PARAMETERS ; 
 int IDC_PROGRAM ; 
 int IDC_RESET_TIME ; 
 int IDC_RESTART_OPTIONS ; 
 int IDC_RESTART_TEXT1 ; 
 int IDC_RESTART_TEXT2 ; 
 int IDC_RESTART_TIME ; 
 int IDC_RUN_GROUPBOX ; 
#define  SC_ACTION_NONE 131 
#define  SC_ACTION_REBOOT 130 
#define  SC_ACTION_RESTART 129 
#define  SC_ACTION_RUN_COMMAND 128 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 scalar_t__ iswspace (int) ; 
 size_t min (int /*<<< orphan*/ ,int) ; 
 int* wcschr (int*,int) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int*) ; 
 int* wcsstr (int*,char*) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static
VOID
ShowFailureActions(
    HWND hwndDlg,
    PRECOVERYDATA pRecoveryData)
{
    WCHAR szBuffer[256];
    PWSTR startPtr, endPtr;
    INT index, id, length;
    DWORD i;

    for (i = 0; i < min(pRecoveryData->pServiceFailure->cActions, 3); i++)
    {
        index = -1;

        switch (pRecoveryData->pServiceFailure->lpsaActions[i].Type)
        {
            case SC_ACTION_NONE:
                index = 0;
                break;

            case SC_ACTION_RESTART:
                index = 1;

                wsprintf(szBuffer, L"%lu", pRecoveryData->pServiceFailure->lpsaActions[i].Delay / 60000);
                SendDlgItemMessageW(hwndDlg,
                                    IDC_RESTART_TIME,
                                    WM_SETTEXT,
                                    0,
                                    (LPARAM)szBuffer);

                for (id = IDC_RESTART_TEXT1; id <= IDC_RESTART_TEXT2; id++)
                     EnableWindow(GetDlgItem(hwndDlg, id), TRUE);
                break;

            case SC_ACTION_REBOOT:
                index = 3;

                EnableWindow(GetDlgItem(hwndDlg, IDC_RESTART_OPTIONS), TRUE);
                break;

            case SC_ACTION_RUN_COMMAND:
                index = 2;

                for (id = IDC_RUN_GROUPBOX; id <= IDC_ADD_FAILCOUNT; id++)
                    EnableWindow(GetDlgItem(hwndDlg, id), TRUE);
                break;
        }

        if (index != -1)
        {
            SendDlgItemMessageW(hwndDlg,
                                IDC_FIRST_FAILURE + i,
                                CB_SETCURSEL,
                                index,
                                0);
        }
    }

    wsprintf(szBuffer, L"%lu", pRecoveryData->pServiceFailure->dwResetPeriod / 86400);
    SendDlgItemMessageW(hwndDlg,
                        IDC_RESET_TIME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)szBuffer);

    if (pRecoveryData->pServiceFailure->lpCommand != NULL)
    {
        ZeroMemory(szBuffer, sizeof(szBuffer));

        startPtr = pRecoveryData->pServiceFailure->lpCommand;
        if (*startPtr == L'\"')
            startPtr++;

        endPtr = wcschr(startPtr, L'\"');
        if (endPtr != NULL)
        {
            length = (INT)((LONG_PTR)endPtr - (LONG_PTR)startPtr);
            CopyMemory(szBuffer, startPtr, length);
        }
        else
        {
            wcscpy(szBuffer, startPtr);
        }

        SendDlgItemMessageW(hwndDlg,
                            IDC_PROGRAM,
                            WM_SETTEXT,
                            0,
                            (LPARAM)szBuffer);

        ZeroMemory(szBuffer, sizeof(szBuffer));

        if (endPtr != NULL)
        {
            startPtr = endPtr + 1;
            while (iswspace(*startPtr))
                startPtr++;

            endPtr = wcsstr(pRecoveryData->pServiceFailure->lpCommand, L"/fail=%1%");
            if (endPtr != NULL)
            {
                while (iswspace(*(endPtr - 1)))
                    endPtr--;

                length = (INT)((LONG_PTR)endPtr - (LONG_PTR)startPtr);
                CopyMemory(szBuffer, startPtr, length);
            }
            else
            {
                wcscpy(szBuffer, startPtr);
            }

            SendDlgItemMessageW(hwndDlg,
                                IDC_PARAMETERS,
                                WM_SETTEXT,
                                0,
                                (LPARAM)szBuffer);

            endPtr = wcsstr(pRecoveryData->pServiceFailure->lpCommand, L"/fail=%1%");
            if (endPtr != NULL)
            {
                SendDlgItemMessageW(hwndDlg,
                                    IDC_ADD_FAILCOUNT,
                                    BM_SETCHECK,
                                    BST_CHECKED,
                                    0);
            }
        }
    }
}