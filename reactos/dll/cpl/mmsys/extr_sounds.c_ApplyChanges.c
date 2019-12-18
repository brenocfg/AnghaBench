#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_8__ {struct TYPE_8__* Next; scalar_t__ szValue; TYPE_2__* LabelMap; TYPE_1__* AppMap; } ;
struct TYPE_7__ {TYPE_4__* LabelContext; scalar_t__ szName; } ;
struct TYPE_6__ {int /*<<< orphan*/  szName; } ;
struct TYPE_5__ {int /*<<< orphan*/  szName; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_3__* PSOUND_SCHEME_CONTEXT ;
typedef  TYPE_4__* PLABEL_CONTEXT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CB_ERR ; 
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  DWLP_MSGRESULT ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDC_SOUND_SCHEME ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 scalar_t__ PSNRET_NOERROR ; 
 int /*<<< orphan*/  REG_EXPAND_SZ ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _tcslen (scalar_t__) ; 

BOOL
ApplyChanges(HWND hwndDlg)
{
    HKEY hKey, hSubKey;
    LRESULT lIndex;
    PSOUND_SCHEME_CONTEXT pScheme;
    HWND hDlgCtrl;
    PLABEL_CONTEXT pLabelContext;
    TCHAR Buffer[100];

    hDlgCtrl = GetDlgItem(hwndDlg, IDC_SOUND_SCHEME);

    lIndex = SendMessage(hDlgCtrl, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
    if (lIndex == CB_ERR)
    {
        return FALSE;
    }

    lIndex = SendMessage(hDlgCtrl, CB_GETITEMDATA, (WPARAM)lIndex, (LPARAM)0);
    if (lIndex == CB_ERR)
    {
        return FALSE;
    }
    pScheme = (PSOUND_SCHEME_CONTEXT)lIndex;

    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     _T("AppEvents\\Schemes"),
                     0,
                     KEY_WRITE,
                     &hKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)pScheme->szName, (_tcslen(pScheme->szName) +1) * sizeof(TCHAR));
    RegCloseKey(hKey);

    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     _T("AppEvents\\Schemes\\Apps"),
                     0,
                     KEY_WRITE,
                     &hKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    pLabelContext = pScheme->LabelContext;

    while (pLabelContext)
    {
        _stprintf(Buffer, _T("%s\\%s\\.Current"), pLabelContext->AppMap->szName, pLabelContext->LabelMap->szName);

        if (RegOpenKeyEx(hKey, Buffer, 0, KEY_WRITE, &hSubKey) == ERROR_SUCCESS)
        {
            RegSetValueEx(hSubKey, NULL, 0, REG_EXPAND_SZ, (LPBYTE)pLabelContext->szValue, (_tcslen(pLabelContext->szValue) +1) * sizeof(TCHAR));
            RegCloseKey(hSubKey);
        }

        pLabelContext = pLabelContext->Next;
    }
    RegCloseKey(hKey);

    SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, (LONG_PTR)PSNRET_NOERROR);
    return TRUE;
}