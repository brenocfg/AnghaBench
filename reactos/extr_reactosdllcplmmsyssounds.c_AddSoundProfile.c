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
typedef  int /*<<< orphan*/  szValue ;
struct TYPE_4__ {int /*<<< orphan*/  szName; int /*<<< orphan*/  szDesc; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  SOUND_SCHEME_CONTEXT ;
typedef  TYPE_1__* PSOUND_SCHEME_CONTEXT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CB_ERR ; 
 scalar_t__ ComboBox_AddString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ComboBox_DeleteString (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ComboBox_SetItemData (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDC_SOUND_SCHEME ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  StringCchCopy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

BOOL
AddSoundProfile(HWND hwndDlg, HKEY hKey, TCHAR * szSubKey, BOOL SetDefault)
{
    HKEY hSubKey;
    TCHAR szValue[MAX_PATH];
    DWORD cbValue, dwResult;
    LRESULT lResult;
    PSOUND_SCHEME_CONTEXT pScheme;

    if (RegOpenKeyEx(hKey,
                     szSubKey,
                     0,
                     KEY_READ,
                     &hSubKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    cbValue = sizeof(szValue);
    dwResult = RegQueryValueEx(hSubKey,
                               NULL,
                               NULL,
                               NULL,
                               (LPBYTE)szValue,
                               &cbValue);
    RegCloseKey(hSubKey);

    if (dwResult != ERROR_SUCCESS)
        return FALSE;

    /* Try to add the new profile */
    lResult = ComboBox_AddString(GetDlgItem(hwndDlg, IDC_SOUND_SCHEME), szValue);
    if (lResult == CB_ERR)
        return FALSE;

    /* Allocate the profile scheme buffer */
    pScheme = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SOUND_SCHEME_CONTEXT));
    if (pScheme == NULL)
    {
        /* We failed to allocate the buffer, no need to keep a dangling string in the combobox */
        ComboBox_DeleteString(GetDlgItem(hwndDlg, IDC_SOUND_SCHEME), lResult);
        return FALSE;
    }

    StringCchCopy(pScheme->szDesc, MAX_PATH, szValue);
    StringCchCopy(pScheme->szName, MAX_PATH, szSubKey);

    /* Associate the value with the item in the combobox */
    ComboBox_SetItemData(GetDlgItem(hwndDlg, IDC_SOUND_SCHEME), lResult, pScheme);

    /* Optionally, select the profile */
    if (SetDefault)
    {
        ComboBox_SetCurSel(GetDlgItem(hwndDlg, IDC_SOUND_SCHEME), lResult);
    }

    return TRUE;
}