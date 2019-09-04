#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_4__ {int dwFlags; int /*<<< orphan*/  iWindowsEffect; } ;
struct TYPE_5__ {scalar_t__ bShowSounds; TYPE_1__ ssSoundSentry; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__* PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_SENTRY_BOX ; 
 int /*<<< orphan*/  IDC_SENTRY_COMBO ; 
 int /*<<< orphan*/  IDC_SENTRY_TEXT ; 
 int /*<<< orphan*/  IDC_SSHOW_BOX ; 
 scalar_t__ IDS_SENTRY_NONE ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int SSF_AVAILABLE ; 
 int SSF_SOUNDSENTRYON ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
OnInitDialog(HWND hwndDlg, PGLOBAL_DATA pGlobalData)
{
    TCHAR szBuffer[256];
    UINT i;

    /* Add strings to the combo-box */
    for (i = 0; i < 4; i++)
    {
        LoadString(hApplet, IDS_SENTRY_NONE + i, szBuffer, 256);
        SendDlgItemMessage(hwndDlg, IDC_SENTRY_COMBO, CB_ADDSTRING, 0, (LPARAM)szBuffer);
    }

    /* Select a combo-box item */
    SendDlgItemMessage(hwndDlg, IDC_SENTRY_COMBO, CB_SETCURSEL, pGlobalData->ssSoundSentry.iWindowsEffect, 0);

    /* Initialize SoundSentry settings */
    if (!(pGlobalData->ssSoundSentry.dwFlags & SSF_AVAILABLE))
    {
        EnableWindow(GetDlgItem(hwndDlg, IDC_SENTRY_BOX), FALSE);
        EnableWindow(GetDlgItem(hwndDlg, IDC_SENTRY_TEXT), FALSE);
        EnableWindow(GetDlgItem(hwndDlg, IDC_SENTRY_COMBO), FALSE);
    }
    else
    {
        if (pGlobalData->ssSoundSentry.dwFlags & SSF_SOUNDSENTRYON)
        {
            CheckDlgButton(hwndDlg, IDC_SENTRY_BOX, BST_CHECKED);
        }
        else
        {
            EnableWindow(GetDlgItem(hwndDlg, IDC_SENTRY_TEXT), FALSE);
            EnableWindow(GetDlgItem(hwndDlg, IDC_SENTRY_COMBO), FALSE);
        }
    }

    /* Initialize ShowSounds settings */
    if (pGlobalData->bShowSounds)
        CheckDlgButton(hwndDlg, IDC_SSHOW_BOX, BST_CHECKED);
}