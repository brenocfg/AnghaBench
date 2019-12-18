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
typedef  int /*<<< orphan*/  szValue ;
typedef  int /*<<< orphan*/  szName ;
typedef  int /*<<< orphan*/  szDefaultOs ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PINT ;
typedef  scalar_t__ PBOOTRECORD ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINF ;
typedef  scalar_t__ DWORD ;

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
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IDC_STRECLIST ; 
 int /*<<< orphan*/  IDC_STRECOSCOMBO ; 
 int MAX_PATH ; 
 scalar_t__ ReadFreeldrSection (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetupFindFirstLineW (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetIntField (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT
LoadFreeldrSettings(HINF hInf, HWND hwndDlg)
{
    INFCONTEXT InfContext;
    PBOOTRECORD pRecord;
    WCHAR szDefaultOs[MAX_PATH];
    WCHAR szName[MAX_PATH];
    WCHAR szValue[MAX_PATH];
    DWORD LineLength;
    DWORD TimeOut;
    LRESULT lResult;

    if (!SetupFindFirstLineW(hInf,
                           L"FREELOADER",
                           L"DefaultOS",
                           &InfContext))
    {
        /* Failed to find default os */
        return FALSE;
    }

    if (!SetupGetStringFieldW(&InfContext,
                             1,
                             szDefaultOs,
                             sizeof(szDefaultOs) / sizeof(WCHAR),
                             &LineLength))
    {
        /* No key */
        return FALSE;
    }

    if (!SetupFindFirstLineW(hInf,
                           L"FREELOADER",
                           L"TimeOut",
                           &InfContext))
    {
        /* Expected to find timeout value */
        return FALSE;
    }


    if (!SetupGetIntField(&InfContext,
                          1,
                          (PINT)&TimeOut))
    {
        /* Failed to retrieve timeout */
        return FALSE;
    }

    if (!SetupFindFirstLineW(hInf,
                           L"Operating Systems",
                           NULL,
                           &InfContext))
    {
       /* Expected list of operating systems */
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
            /* The ini file is messed up */
            return FALSE;
        }

        if (!SetupGetStringFieldW(&InfContext,
                                 1,
                                 szValue,
                                 sizeof(szValue) / sizeof(WCHAR),
                                 &LineLength))
        {
            /* The ini file is messed up */
            return FALSE;
        }

        pRecord = ReadFreeldrSection(hInf, szName);
        if (pRecord)
        {
            lResult = SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_ADDSTRING, (WPARAM)0, (LPARAM)szValue);
            if (lResult != CB_ERR)
            {
                SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_SETITEMDATA, (WPARAM)lResult, (LPARAM)pRecord);
                if (!wcscmp(szDefaultOs, szName))
                {
                    /* We store the friendly name as key */
                    wcscpy(szDefaultOs, szValue);
                }
            }
            else
            {
               HeapFree(GetProcessHeap(), 0, pRecord);
            }
        }
    }
    while (SetupFindNextLine(&InfContext, &InfContext));

    /* Find default os in list */
    lResult = SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_FINDSTRING, (WPARAM)-1, (LPARAM)szDefaultOs);
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