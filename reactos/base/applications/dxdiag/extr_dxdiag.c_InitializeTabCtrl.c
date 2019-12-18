#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ NumSoundAdapter; scalar_t__ NumDisplayAdapter; void** hDialogs; int /*<<< orphan*/  hTabCtrl; } ;
typedef  TYPE_1__* PDXDIAG_CONTEXT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 void* CreateDialogParamW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableDialogTheme (void*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HelpPageWndProc ; 
 int /*<<< orphan*/  IDC_TAB_CONTROL ; 
 int /*<<< orphan*/  IDD_HELP_DIALOG ; 
 int /*<<< orphan*/  IDD_INPUT_DIALOG ; 
 int /*<<< orphan*/  IDD_MUSIC_DIALOG ; 
 int /*<<< orphan*/  IDD_NETWORK_DIALOG ; 
 int /*<<< orphan*/  IDD_SYSTEM_DIALOG ; 
 int /*<<< orphan*/  IDS_HELP_DIALOG ; 
 int /*<<< orphan*/  IDS_INPUT_DIALOG ; 
 int /*<<< orphan*/  IDS_MUSIC_DIALOG ; 
 int /*<<< orphan*/  IDS_NETWORK_DIALOG ; 
 int /*<<< orphan*/  IDS_SYSTEM_DIALOG ; 
 int /*<<< orphan*/  InitializeDirectSoundPage (TYPE_1__*) ; 
 int /*<<< orphan*/  InitializeDisplayAdapters (TYPE_1__*) ; 
 int /*<<< orphan*/  InputPageWndProc ; 
 int /*<<< orphan*/  InsertTabCtrlItem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MusicPageWndProc ; 
 int /*<<< orphan*/  NetworkPageWndProc ; 
 int /*<<< orphan*/  SystemPageWndProc ; 
 int /*<<< orphan*/  TabCtrl_OnSelChange (TYPE_1__*) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hTabCtrlWnd ; 

VOID
InitializeTabCtrl(HWND hwndDlg, PDXDIAG_CONTEXT pContext)
{
    /* get tabctrl */
    hTabCtrlWnd = GetDlgItem(hwndDlg, IDC_TAB_CONTROL);
    pContext->hTabCtrl = hTabCtrlWnd;

    /* create the dialogs */
    pContext->hDialogs[0] = CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_SYSTEM_DIALOG), pContext->hTabCtrl, SystemPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->hDialogs[0]);
    pContext->hDialogs[1] = CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_MUSIC_DIALOG), pContext->hTabCtrl, MusicPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->hDialogs[1]);
    pContext->hDialogs[2] = CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_INPUT_DIALOG), pContext->hTabCtrl, InputPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->hDialogs[2]);
    pContext->hDialogs[3] = CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_NETWORK_DIALOG), pContext->hTabCtrl, NetworkPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->hDialogs[3]);
    pContext->hDialogs[4] = CreateDialogParamW(hInst, MAKEINTRESOURCEW(IDD_HELP_DIALOG), pContext->hTabCtrl, HelpPageWndProc, (LPARAM)pContext); EnableDialogTheme(pContext->hDialogs[4]);

    /* insert tab ctrl items */
    InsertTabCtrlItem(hTabCtrlWnd, 0, MAKEINTRESOURCEW(IDS_SYSTEM_DIALOG));
    InitializeDisplayAdapters(pContext);
    InitializeDirectSoundPage(pContext);
    InsertTabCtrlItem(hTabCtrlWnd, pContext->NumDisplayAdapter + pContext->NumSoundAdapter + 1, MAKEINTRESOURCEW(IDS_MUSIC_DIALOG));
    InsertTabCtrlItem(hTabCtrlWnd, pContext->NumDisplayAdapter + pContext->NumSoundAdapter + 2, MAKEINTRESOURCEW(IDS_INPUT_DIALOG));
    InsertTabCtrlItem(hTabCtrlWnd, pContext->NumDisplayAdapter + pContext->NumSoundAdapter + 3, MAKEINTRESOURCEW(IDS_NETWORK_DIALOG));
    InsertTabCtrlItem(hTabCtrlWnd, pContext->NumDisplayAdapter + pContext->NumSoundAdapter + 4, MAKEINTRESOURCEW(IDS_HELP_DIALOG));
    TabCtrl_OnSelChange(pContext);
}