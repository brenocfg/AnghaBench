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
typedef  int /*<<< orphan*/  PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ EnumerateSoundProfiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  ImportSoundProfiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 

BOOL
LoadSoundProfiles(PGLOBAL_DATA pGlobalData, HWND hwndDlg)
{
    HKEY hSubKey;
    DWORD dwNumSchemes;

    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     _T("AppEvents\\Schemes"),
                     0,
                     KEY_READ,
                     &hSubKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    dwNumSchemes = EnumerateSoundProfiles(pGlobalData, hwndDlg, hSubKey);


    if (dwNumSchemes)
    {
        //MessageBox(hwndDlg, _T("importing sound profiles..."), NULL, MB_OK);
        ImportSoundProfiles(pGlobalData, hwndDlg, hSubKey);
    }

    RegCloseKey(hSubKey);
    return FALSE;
}