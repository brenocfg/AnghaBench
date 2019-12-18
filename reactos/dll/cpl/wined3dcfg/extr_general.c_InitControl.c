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
typedef  int /*<<< orphan*/  szBuffer ;
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {scalar_t__ iValue; scalar_t__ szValue; } ;
typedef  TYPE_1__* PWINED3D_SETTINGS ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int MAX_KEY_LENGTH ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscmp (scalar_t__*,scalar_t__) ; 

void InitControl(HWND hWndDlg, HKEY hKey, PWCHAR szKey, PWINED3D_SETTINGS pSettings, INT iControlId, INT iCount)
{
    WCHAR szBuffer[MAX_KEY_LENGTH];
    DWORD dwSize = sizeof(szBuffer);
    DWORD dwType = 0;
    INT iCurrent;
    INT iActive = 0;

    RegQueryValueExW(hKey, szKey, NULL, &dwType, (LPBYTE)szBuffer, &dwSize);

    for(iCurrent = 0; iCurrent < iCount; iCurrent++)
    {
        SendDlgItemMessageW(hWndDlg, iControlId, CB_ADDSTRING, 0, (LPARAM)pSettings[iCurrent].szValue);

        if(dwSize && ((dwType == REG_DWORD && *szBuffer == pSettings[iCurrent].iValue) ||
           (dwType == REG_SZ && !wcscmp(szBuffer, pSettings[iCurrent].szValue))))
        {
            iActive = iCurrent;
        }
    }

    SendDlgItemMessageW(hWndDlg, iControlId, CB_SETCURSEL, iActive, 0);

}