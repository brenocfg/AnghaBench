#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_8__ {int Selection; TYPE_1__* ScreenSaverItems; } ;
struct TYPE_7__ {scalar_t__ szDisplayName; int /*<<< orphan*/  szFilename; } ;
typedef  TYPE_2__* PDATA ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DATA ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddScreenSavers (int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t CB_ERR ; 
 int /*<<< orphan*/  CB_FINDSTRINGEXACT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CheckRegScreenSaverIsSecure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWLP_USER ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetCurrentScreenSaverValue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IDC_SCREENS_LIST ; 
 int /*<<< orphan*/  IDC_SCREENS_TIME ; 
 int MAKELONG (short,short) ; 
 size_t MAX_SCREENSAVERS ; 
 int /*<<< orphan*/  SelectionChanged (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UDM_SETPOS32 ; 
 int /*<<< orphan*/  UDM_SETRANGE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int _ttoi (scalar_t__) ; 

__attribute__((used)) static BOOL
OnInitDialog(HWND hwndDlg, PDATA pData)
{
    LPTSTR lpCurSs;
    HWND hwndSSCombo = GetDlgItem(hwndDlg, IDC_SCREENS_LIST);
    INT Num;

    pData = HeapAlloc(GetProcessHeap(),
                            HEAP_ZERO_MEMORY,
                            sizeof(DATA));
    if (!pData)
    {
        EndDialog(hwndDlg, -1);
        return FALSE;
    }

    SetWindowLongPtr(hwndDlg,
                     DWLP_USER,
                     (LONG_PTR)pData);

    pData->Selection = -1;

    SendDlgItemMessage(hwndDlg,
                       IDC_SCREENS_TIME,
                       UDM_SETRANGE,
                       0,
                       MAKELONG
                       ((short) 240, (short) 1));

    AddScreenSavers(hwndDlg,
                    pData);

    CheckRegScreenSaverIsSecure(hwndDlg);

    /* Set the current screensaver in the combo box */
    lpCurSs = GetCurrentScreenSaverValue(_T("SCRNSAVE.EXE"));
    if (lpCurSs)
    {
        BOOL bFound = FALSE;
        INT i;

        for (i = 0; i < MAX_SCREENSAVERS; i++)
        {
            if (!_tcscmp(lpCurSs, pData->ScreenSaverItems[i].szFilename))
            {
                bFound = TRUE;
                break;
            }
        }

        if (bFound)
        {
            Num = SendMessage(hwndSSCombo,
                              CB_FINDSTRINGEXACT,
                              -1,
                              (LPARAM)pData->ScreenSaverItems[i].szDisplayName);
            if (Num != CB_ERR)
                SendMessage(hwndSSCombo,
                            CB_SETCURSEL,
                            Num,
                            0);
        }
        else
        {
            SendMessage(hwndSSCombo,
                        CB_SETCURSEL,
                        0,
                        0);
        }

        HeapFree(GetProcessHeap(),
                 0,
                 lpCurSs);
    }
    else
    {
        /* Set screensaver to (none) */
        SendMessage(hwndSSCombo,
                    CB_SETCURSEL,
                    0,
                    0);
    }

    /* Set the current timeout */
    lpCurSs = GetCurrentScreenSaverValue(_T("ScreenSaveTimeOut"));
    if (lpCurSs)
    {
        UINT Time = _ttoi(lpCurSs);

        Time /= 60;

        SendDlgItemMessage(hwndDlg,
                           IDC_SCREENS_TIME,
                           UDM_SETPOS32,
                           0,
                           Time);

        HeapFree(GetProcessHeap(),
                 0,
                 lpCurSs);

    }

    SelectionChanged(hwndDlg,
                     pData);

    return TRUE;
}