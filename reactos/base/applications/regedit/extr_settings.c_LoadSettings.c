#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tConfig ;
typedef  int /*<<< orphan*/  WINDOWPLACEMENT ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {int length; } ;
struct TYPE_8__ {int /*<<< orphan*/  hTreeWnd; int /*<<< orphan*/  nSplitPos; int /*<<< orphan*/  hListWnd; } ;
struct TYPE_7__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_6__ {TYPE_4__ tPlacement; int /*<<< orphan*/  TreeViewSize; int /*<<< orphan*/  DataColumnSize; int /*<<< orphan*/  TypeColumnSize; int /*<<< orphan*/  NameColumnSize; scalar_t__ StatusBarVisible; } ;
typedef  TYPE_1__ RegistryBinaryConfig ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT_OF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  ID_VIEW_MENU ; 
 int /*<<< orphan*/  ID_VIEW_STATUSBAR ; 
 int /*<<< orphan*/  ListView_SetColumnWidth (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int MF_UNCHECKED ; 
 scalar_t__ QueryStringValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ResizeWnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SelectNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowPlacement (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* g_pChildWnd ; 
 int /*<<< orphan*/  g_szGeneralRegKey ; 
 int /*<<< orphan*/  hFrameWnd ; 
 int /*<<< orphan*/  hMenuFrame ; 
 int /*<<< orphan*/  hStatusBar ; 

extern void LoadSettings(void)
{
    HKEY hKey = NULL;
    WCHAR szBuffer[MAX_PATH];

    if (RegOpenKeyW(HKEY_CURRENT_USER, g_szGeneralRegKey, &hKey) == ERROR_SUCCESS)
    {
        RegistryBinaryConfig tConfig;
        DWORD iBufferSize = sizeof(tConfig);
        BOOL bVisible = FALSE;

        if (RegQueryValueExW(hKey, L"View", NULL, NULL, (LPBYTE)&tConfig, &iBufferSize) == ERROR_SUCCESS)
        {
            if (iBufferSize == sizeof(tConfig))
            {
                RECT rcTemp;

                /* Update status bar settings */
                CheckMenuItem(GetSubMenu(hMenuFrame, ID_VIEW_MENU), ID_VIEW_STATUSBAR, MF_BYCOMMAND | (tConfig.StatusBarVisible ? MF_CHECKED : MF_UNCHECKED));
                ShowWindow(hStatusBar, (tConfig.StatusBarVisible ? SW_SHOW : SW_HIDE));

                /* Update listview column width */
                (void)ListView_SetColumnWidth(g_pChildWnd->hListWnd, 0, tConfig.NameColumnSize);
                (void)ListView_SetColumnWidth(g_pChildWnd->hListWnd, 1, tConfig.TypeColumnSize);
                (void)ListView_SetColumnWidth(g_pChildWnd->hListWnd, 2, tConfig.DataColumnSize);

                /* Update treeview (splitter) */
                GetClientRect(hFrameWnd, &rcTemp);
                g_pChildWnd->nSplitPos = tConfig.TreeViewSize;
                ResizeWnd(rcTemp.right, rcTemp.bottom);

                /* Apply program window settings */
                tConfig.tPlacement.length = sizeof(WINDOWPLACEMENT);
                bVisible = SetWindowPlacement(hFrameWnd, &tConfig.tPlacement);
            }
        }

        /* In case we fail to restore the window, or open the key, show normal */
        if (!bVisible)
            ShowWindow(hFrameWnd, SW_SHOWNORMAL);

        /* Restore key position */
        if (QueryStringValue(HKEY_CURRENT_USER, g_szGeneralRegKey, L"LastKey", szBuffer, COUNT_OF(szBuffer)) == ERROR_SUCCESS)
        {
            SelectNode(g_pChildWnd->hTreeWnd, szBuffer);
        }

        RegCloseKey(hKey);
    }
    else
    {
        /* Failed to open key, show normal */
        ShowWindow(hFrameWnd, SW_SHOWNORMAL);
    }
}