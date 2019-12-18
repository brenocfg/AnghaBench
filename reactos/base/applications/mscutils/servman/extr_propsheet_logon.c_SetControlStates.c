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
struct TYPE_3__ {scalar_t__ bInitialized; char* szAccountName; char* szPassword1; char* szPassword2; int bLocalSystem; scalar_t__ nInteractive; } ;
typedef  TYPE_1__* PLOGONDATA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_GETCHECK ; 
 int /*<<< orphan*/  BM_SETCHECK ; 
 scalar_t__ BST_UNCHECKED ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IDC_LOGON_ACCOUNTNAME ; 
 int /*<<< orphan*/  IDC_LOGON_INTERACTIVE ; 
 int /*<<< orphan*/  IDC_LOGON_PASSWORD1 ; 
 int /*<<< orphan*/  IDC_LOGON_PASSWORD2 ; 
 int /*<<< orphan*/  IDC_LOGON_PW1TEXT ; 
 int /*<<< orphan*/  IDC_LOGON_PW2TEXT ; 
 int /*<<< orphan*/  IDC_LOGON_SEARCH ; 
 scalar_t__ SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static
VOID
SetControlStates(
    HWND hwndDlg,
    PLOGONDATA pLogonData,
    BOOL bLocalSystem)
{
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_INTERACTIVE), bLocalSystem);
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_ACCOUNTNAME), !bLocalSystem);
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_SEARCH), FALSE /*!bLocalSystem*/);
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_PW1TEXT), !bLocalSystem);
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_PASSWORD1), !bLocalSystem);
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_PW2TEXT), !bLocalSystem);
    EnableWindow(GetDlgItem(hwndDlg, IDC_LOGON_PASSWORD2), !bLocalSystem);

    if (bLocalSystem)
    {
        SendDlgItemMessageW(hwndDlg, IDC_LOGON_INTERACTIVE, BM_SETCHECK, (WPARAM)pLogonData->nInteractive, 0);

        if (pLogonData->bInitialized == TRUE)
        {
            GetDlgItemText(hwndDlg, IDC_LOGON_ACCOUNTNAME, pLogonData->szAccountName, 64);
            GetDlgItemText(hwndDlg, IDC_LOGON_PASSWORD1, pLogonData->szPassword1, 64);
            GetDlgItemText(hwndDlg, IDC_LOGON_PASSWORD2, pLogonData->szPassword2, 64);
        }

        SetDlgItemText(hwndDlg, IDC_LOGON_ACCOUNTNAME, L"");
        SetDlgItemText(hwndDlg, IDC_LOGON_PASSWORD1, L"");
        SetDlgItemText(hwndDlg, IDC_LOGON_PASSWORD2, L"");
    }
    else
    {
        if (pLogonData->bInitialized == TRUE)
            pLogonData->nInteractive = SendDlgItemMessageW(hwndDlg, IDC_LOGON_INTERACTIVE, BM_GETCHECK, 0, 0);
        SendDlgItemMessageW(hwndDlg, IDC_LOGON_INTERACTIVE, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);

        SetDlgItemText(hwndDlg, IDC_LOGON_ACCOUNTNAME, pLogonData->szAccountName);
        SetDlgItemText(hwndDlg, IDC_LOGON_PASSWORD1, pLogonData->szPassword1);
        SetDlgItemText(hwndDlg, IDC_LOGON_PASSWORD2, pLogonData->szPassword2);
    }

    pLogonData->bLocalSystem = bLocalSystem;
}