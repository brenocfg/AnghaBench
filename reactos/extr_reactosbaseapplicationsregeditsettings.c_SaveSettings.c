#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tConfig ;
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int /*<<< orphan*/  WINDOWPLACEMENT ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {int /*<<< orphan*/  hListWnd; int /*<<< orphan*/  nSplitPos; int /*<<< orphan*/  hTreeWnd; } ;
struct TYPE_4__ {int StatusBarVisible; TYPE_3__ tPlacement; void* DataColumnSize; void* TypeColumnSize; void* NameColumnSize; int /*<<< orphan*/  TreeViewSize; } ;
typedef  TYPE_1__ RegistryBinaryConfig ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT_OF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DbgPrint (char*,char*,int,char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 char* GetItemPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GetMenuState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowPlacement (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDS_MY_COMPUTER ; 
 int /*<<< orphan*/  ID_VIEW_MENU ; 
 int /*<<< orphan*/  ID_VIEW_STATUSBAR ; 
 void* ListView_GetColumnWidth (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringCbCatW (int /*<<< orphan*/ *,int,char*) ; 
 TYPE_2__* g_pChildWnd ; 
 int /*<<< orphan*/  g_szGeneralRegKey ; 
 char* get_root_key_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hFrameWnd ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMenuFrame ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

extern void SaveSettings(void)
{
    HKEY hKey = NULL;

    if (RegCreateKeyW(HKEY_CURRENT_USER, g_szGeneralRegKey, &hKey) == ERROR_SUCCESS)
    {
        RegistryBinaryConfig tConfig;
        DWORD iBufferSize = sizeof(tConfig);
        WCHAR szBuffer[MAX_PATH]; /* FIXME: a complete registry path can be longer than that */
        LPCWSTR keyPath, rootName;
        HKEY hRootKey;

        /* Save key position */
        keyPath = GetItemPath(g_pChildWnd->hTreeWnd, 0, &hRootKey);
        rootName = get_root_key_name(hRootKey);

        /* Load "My Computer" string and complete it */
        if (LoadStringW(hInst, IDS_MY_COMPUTER, szBuffer, COUNT_OF(szBuffer)) &&
            SUCCEEDED(StringCbCatW(szBuffer, sizeof(szBuffer), L"\\")) &&
            SUCCEEDED(StringCbCatW(szBuffer, sizeof(szBuffer), rootName)) &&
            SUCCEEDED(StringCbCatW(szBuffer, sizeof(szBuffer), L"\\")))
        {
            HRESULT hr = S_OK;
            if (keyPath)
                hr = StringCbCatW(szBuffer, sizeof(szBuffer), keyPath);
            if (SUCCEEDED(hr))
                RegSetValueExW(hKey, L"LastKey", 0, REG_SZ, (LPBYTE)szBuffer, (DWORD)wcslen(szBuffer) * sizeof(WCHAR));
            else
                DbgPrint("err: (%s:%d): Buffer not big enough for '%S + %S'\n", __FILE__, __LINE__, rootName, keyPath);
        }
        else
        {
            DbgPrint("err: (%s:%d): Buffer not big enough for '%S'\n", __FILE__, __LINE__, rootName);
        }

        /* Get statusbar settings */
        tConfig.StatusBarVisible = ((GetMenuState(GetSubMenu(hMenuFrame, ID_VIEW_MENU), ID_VIEW_STATUSBAR, MF_BYCOMMAND) & MF_CHECKED) ? 1 : 0);

        /* Get splitter position */
        tConfig.TreeViewSize = g_pChildWnd->nSplitPos;

        /* Get list view column width*/
        tConfig.NameColumnSize = ListView_GetColumnWidth(g_pChildWnd->hListWnd, 0);
        tConfig.TypeColumnSize = ListView_GetColumnWidth(g_pChildWnd->hListWnd, 1);
        tConfig.DataColumnSize = ListView_GetColumnWidth(g_pChildWnd->hListWnd, 2);

        /* Get program window settings */
        tConfig.tPlacement.length = sizeof(WINDOWPLACEMENT);
        GetWindowPlacement(hFrameWnd, &tConfig.tPlacement);

        /* Save all the data */
        RegSetValueExW(hKey, L"View", 0, REG_BINARY, (LPBYTE)&tConfig, iBufferSize);

        RegCloseKey(hKey);
    }
}