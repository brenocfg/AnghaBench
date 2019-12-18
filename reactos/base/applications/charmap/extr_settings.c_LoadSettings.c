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
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CLICK ; 
 int CB_ERR ; 
 int /*<<< orphan*/  ChangeMapFont (int /*<<< orphan*/ ) ; 
 int ComboBox_FindStringExact (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDC_CHECK_ADVANCED ; 
 int /*<<< orphan*/  IDC_COMBO_CHARSET ; 
 int /*<<< orphan*/  IDC_FONTCOMBO ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MF_CHECKED ; 
 scalar_t__ QueryStringValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned long REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegQueryValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  g_szGeneralRegKey ; 
 int /*<<< orphan*/  hCharmapDlg ; 
 int /*<<< orphan*/  hWnd ; 

extern void LoadSettings(void)
{
    HKEY hKey = NULL;
    int iItemIndex = -1;

    if (RegOpenKeyEx(HKEY_CURRENT_USER, g_szGeneralRegKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        TCHAR szBuffer[MAX_PATH];
        DWORD dwAdvancedChecked;
        unsigned long type = REG_DWORD, size = 1024;

        /* Restore last selected font */
        if (QueryStringValue(HKEY_CURRENT_USER, g_szGeneralRegKey, _T("Font"), szBuffer, (sizeof(szBuffer)/sizeof(szBuffer[0]))) == ERROR_SUCCESS)
        {
            //Get combobox handle
            hWnd = GetDlgItem(hCharmapDlg, IDC_FONTCOMBO);

            //Search for match and return index if match found
            iItemIndex = ComboBox_FindStringExact(hWnd, -1, szBuffer);
            if(iItemIndex != CB_ERR)
            {
                ComboBox_SetCurSel(hWnd, iItemIndex);
                ChangeMapFont(hCharmapDlg);
            }
        }

        /* Restore last selected character set */
        if (QueryStringValue(HKEY_CURRENT_USER, g_szGeneralRegKey, _T("CodePage"), szBuffer, (sizeof(szBuffer)/sizeof(szBuffer[0]))) == ERROR_SUCCESS)
        {
            //Get combobox handle
            hWnd = GetDlgItem(hCharmapDlg, IDC_COMBO_CHARSET);

            iItemIndex = ComboBox_FindStringExact(hWnd, -1, szBuffer);
            if(iItemIndex != CB_ERR)
            {
                ComboBox_SetCurSel(hWnd, iItemIndex);
            }
        }

        RegQueryValueEx(hKey, _T("Advanced"), NULL, &type, (LPBYTE)&dwAdvancedChecked, &size);

        if(dwAdvancedChecked != FALSE)
            SendDlgItemMessage(hCharmapDlg, IDC_CHECK_ADVANCED, BM_CLICK, MF_CHECKED, 0);

    RegCloseKey(hKey);
    }
    else
    {
        /* Default font seems to be Arial */
        hWnd = GetDlgItem(hCharmapDlg, IDC_FONTCOMBO);

        iItemIndex = ComboBox_FindStringExact(hWnd, -1, _T("Arial"));
        if(iItemIndex != CB_ERR)
        {
            ComboBox_SetCurSel(hWnd, iItemIndex);
            ChangeMapFont(hCharmapDlg);
        }
    }
}