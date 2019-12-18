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
typedef  int /*<<< orphan*/  szValue ;
typedef  int /*<<< orphan*/  szOptions ;
typedef  int /*<<< orphan*/  szName ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * szOptions; int /*<<< orphan*/ * szSectionName; int /*<<< orphan*/ * szBootPath; scalar_t__ BootType; } ;
typedef  TYPE_1__* PBOOTRECORD ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINF ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOTRECORD ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETCHECK ; 
 scalar_t__ BST_CHECKED ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 scalar_t__ CB_ERR ; 
 int /*<<< orphan*/  CB_FINDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CB_SETITEMDATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_STRECLIST ; 
 int /*<<< orphan*/  IDC_STRECOSCOMBO ; 
 int MAX_PATH ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetupFindFirstLineW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _wcsnicmp (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ _wtoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT
LoadBootSettings(HINF hInf, HWND hwndDlg)
{
    INFCONTEXT InfContext;
    WCHAR szName[MAX_PATH];
    WCHAR szValue[MAX_PATH];
    DWORD LineLength;
    DWORD TimeOut = 0;
    WCHAR szDefaultOS[MAX_PATH];
    WCHAR szOptions[MAX_PATH];
    PBOOTRECORD pRecord;
    LRESULT lResult;

    if(!SetupFindFirstLineW(hInf,
                           L"boot loader",
                           NULL,
                           &InfContext))
    {
        return FALSE;
    }

    do
    {
        if (!SetupGetStringFieldW(&InfContext,
                                 0,
                                 szName,
                                 sizeof(szName) / sizeof(WCHAR),
                                 &LineLength))
        {
            return FALSE;
        }

        if (!SetupGetStringFieldW(&InfContext,
                                 1,
                                 szValue,
                                 sizeof(szValue) / sizeof(WCHAR),
                                 &LineLength))
        {
            return FALSE;
        }

        if (!_wcsnicmp(szName, L"timeout", 7))
        {
            TimeOut = _wtoi(szValue);
        }

        if (!_wcsnicmp(szName, L"default", 7))
        {
            wcscpy(szDefaultOS, szValue);
        }

    }
    while (SetupFindNextLine(&InfContext, &InfContext));

    if (!SetupFindFirstLineW(hInf,
                            L"operating systems",
                            NULL,
                            &InfContext))
    {
        /* Failed to find operating systems section */
        return FALSE;
    }

    do
    {
        if (!SetupGetStringFieldW(&InfContext,
                                 0,
                                 szName,
                                 sizeof(szName) / sizeof(WCHAR),
                                 &LineLength))
        {
            return FALSE;
        }

        if (!SetupGetStringFieldW(&InfContext,
                                 1,
                                 szValue,
                                 sizeof(szValue) / sizeof(WCHAR),
                                 &LineLength))
        {
            return FALSE;
        }

        SetupGetStringFieldW(&InfContext,
                            2,
                            szOptions,
                            sizeof(szOptions) / sizeof(WCHAR),
                            &LineLength);

        pRecord = (PBOOTRECORD) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(BOOTRECORD));
        if (pRecord)
        {
            pRecord->BootType = 0;
            wcscpy(pRecord->szBootPath, szName);
            wcscpy(pRecord->szSectionName, szValue);
            wcscpy(pRecord->szOptions, szOptions);

            if (!wcscmp(szName, szDefaultOS))
            {
                /* ms boot ini stores the path not the friendly name */
                wcscpy(szDefaultOS, szValue);
            }

            lResult = SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_ADDSTRING, (WPARAM)0, (LPARAM)szValue);
            if (lResult != CB_ERR)
            {
                SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_SETITEMDATA, (WPARAM)lResult, (LPARAM)pRecord);
            }
            else
            {
               HeapFree(GetProcessHeap(), 0, pRecord);
            }
        }

    }
    while (SetupFindNextLine(&InfContext, &InfContext));

    /* Find default os in list */
    lResult = SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_FINDSTRING, (WPARAM)0, (LPARAM)szDefaultOS);
    if (lResult != CB_ERR)
    {
       /* Set cur sel */
       SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_SETCURSEL, (WPARAM)lResult, (LPARAM)0);
    }

    if(TimeOut)
    {
        SendDlgItemMessageW(hwndDlg, IDC_STRECLIST, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
    }

    SetTimeout(hwndDlg, TimeOut);

    return TRUE;
}