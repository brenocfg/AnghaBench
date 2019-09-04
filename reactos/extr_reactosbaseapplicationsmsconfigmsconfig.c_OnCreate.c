#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pszText; void* mask; } ;
typedef  TYPE_1__ TCITEM ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableDialogTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLdrPageWndProc ; 
 int /*<<< orphan*/  GeneralPageWndProc ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_TAB ; 
 int /*<<< orphan*/  IDD_FREELDR_PAGE ; 
 int /*<<< orphan*/  IDD_GENERAL_PAGE ; 
 int /*<<< orphan*/  IDD_SERVICES_PAGE ; 
 int /*<<< orphan*/  IDD_STARTUP_PAGE ; 
 int /*<<< orphan*/  IDD_SYSTEM_PAGE ; 
 int /*<<< orphan*/  IDD_TOOLS_PAGE ; 
 int /*<<< orphan*/  IDS_MSCONFIG ; 
 int /*<<< orphan*/  IDS_TAB_FREELDR ; 
 int /*<<< orphan*/  IDS_TAB_GENERAL ; 
 int /*<<< orphan*/  IDS_TAB_SERVICES ; 
 int /*<<< orphan*/  IDS_TAB_STARTUP ; 
 int /*<<< orphan*/  IDS_TAB_SYSTEM ; 
 int /*<<< orphan*/  IDS_TAB_TOOLS ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsConfig_OnTabWndSelChange () ; 
 int /*<<< orphan*/  ServicesPageWndProc ; 
 int /*<<< orphan*/  SetWindowText (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartupPageWndProc ; 
 int /*<<< orphan*/  SystemPageWndProc ; 
 void* TCIF_TEXT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TabCtrl_InsertItem (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ToolsPageWndProc ; 
 int /*<<< orphan*/  hFreeLdrPage ; 
 int /*<<< orphan*/  hGeneralPage ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hServicesPage ; 
 int /*<<< orphan*/  hStartupPage ; 
 int /*<<< orphan*/  hSystemPage ; 
 int /*<<< orphan*/  hTabWnd ; 
 int /*<<< orphan*/  hToolsPage ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOL OnCreate(HWND hWnd)
{
    TCHAR   szTemp[256];
    TCITEM  item;

    hTabWnd = GetDlgItem(hWnd, IDC_TAB);
    hGeneralPage = CreateDialog(hInst, MAKEINTRESOURCE(IDD_GENERAL_PAGE), hWnd,  GeneralPageWndProc); EnableDialogTheme(hGeneralPage);
    hSystemPage = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SYSTEM_PAGE), hWnd,  SystemPageWndProc); EnableDialogTheme(hSystemPage);
    hFreeLdrPage = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FREELDR_PAGE), hWnd,  FreeLdrPageWndProc); EnableDialogTheme(hFreeLdrPage);
    hServicesPage = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SERVICES_PAGE), hWnd,  ServicesPageWndProc); EnableDialogTheme(hServicesPage);
    hStartupPage = CreateDialog(hInst, MAKEINTRESOURCE(IDD_STARTUP_PAGE), hWnd,  StartupPageWndProc); EnableDialogTheme(hStartupPage);
    hToolsPage = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TOOLS_PAGE), hWnd,  ToolsPageWndProc); EnableDialogTheme(hToolsPage);

    LoadString(hInst, IDS_MSCONFIG, szTemp, 256);
    SetWindowText(hWnd, szTemp);

    // Insert Tab Pages
    LoadString(hInst, IDS_TAB_GENERAL, szTemp, 256);
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    (void)TabCtrl_InsertItem(hTabWnd, 0, &item);

    LoadString(hInst, IDS_TAB_SYSTEM, szTemp, 256);
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    (void)TabCtrl_InsertItem(hTabWnd, 1, &item);

    LoadString(hInst, IDS_TAB_FREELDR, szTemp, 256);
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    (void)TabCtrl_InsertItem(hTabWnd, 2, &item);

    LoadString(hInst, IDS_TAB_SERVICES, szTemp, 256);
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    (void)TabCtrl_InsertItem(hTabWnd, 3, &item);

    LoadString(hInst, IDS_TAB_STARTUP, szTemp, 256);
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    (void)TabCtrl_InsertItem(hTabWnd, 4, &item);

    LoadString(hInst, IDS_TAB_TOOLS, szTemp, 256);
    memset(&item, 0, sizeof(TCITEM));
    item.mask = TCIF_TEXT;
    item.pszText = szTemp;
    (void)TabCtrl_InsertItem(hTabWnd, 5, &item);

    MsConfig_OnTabWndSelChange();

    return TRUE;
}