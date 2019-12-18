#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IsAdvancedView; } ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ComboBox_GetText (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDC_COMBO_CHARSET ; 
 int /*<<< orphan*/  IDC_FONTCOMBO ; 
 int /*<<< orphan*/  KEY_SET_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ Settings ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  g_szGeneralRegKey ; 
 int /*<<< orphan*/  hCharmapDlg ; 
 int /*<<< orphan*/  hWnd ; 

extern void SaveSettings(void)
{
    HKEY hKey = NULL;

    if (RegCreateKeyEx(HKEY_CURRENT_USER, g_szGeneralRegKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL) == ERROR_SUCCESS)
    {
        TCHAR szBuffer[MAX_PATH];

        hWnd = GetDlgItem(hCharmapDlg, IDC_FONTCOMBO);
        ComboBox_GetText(hWnd, szBuffer, MAX_PATH);

        if(*szBuffer != '\0')
            RegSetValueEx(hKey, _T("Font"), 0, REG_SZ, (LPBYTE) szBuffer, (DWORD) MAX_PATH);

        hWnd = GetDlgItem(hCharmapDlg, IDC_COMBO_CHARSET);
        ComboBox_GetText(hWnd, szBuffer, MAX_PATH);

        if(*szBuffer != '\0')
            RegSetValueEx(hKey, _T("CodePage"), 0, REG_SZ, (LPBYTE) szBuffer, (DWORD) MAX_PATH);

        RegSetValueEx(hKey, _T("Advanced"), 0, REG_DWORD, (LPBYTE)&Settings.IsAdvancedView, (DWORD) sizeof(DWORD));

        RegCloseKey(hKey);
    }
}