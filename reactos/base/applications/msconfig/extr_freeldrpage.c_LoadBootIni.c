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
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int WCHAR ;
typedef  int UINT ;
struct TYPE_2__ {int OSConfigurationCount; int /*<<< orphan*/  TimeOut; scalar_t__ szDefaultPos; scalar_t__ szDefaultOS; int /*<<< orphan*/  UseBootIni; } ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_BTN_MOVE_DOWN_BOOT_OPTION ; 
 int /*<<< orphan*/  IDC_BTN_MOVE_UP_BOOT_OPTION ; 
 int /*<<< orphan*/  IDC_BTN_SET_DEFAULT_BOOT ; 
 int /*<<< orphan*/  IDC_LIST_BOX ; 
 int /*<<< orphan*/  IDC_TXT_BOOT_TIMEOUT ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_FINDSTRING ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ Settings ; 
 int /*<<< orphan*/  StringCbCatW (int*,int,char*) ; 
 int /*<<< orphan*/  StringCbCopyW (int*,int,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _wcsnicmp (int*,char*,int) ; 
 int /*<<< orphan*/ * _wfopen (int*,char*) ; 
 int /*<<< orphan*/  _wtoi (int*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgetws (int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__,int*) ; 
 int wcslen (int*) ; 

__attribute__((used)) static BOOL
LoadBootIni(WCHAR *szDrive, HWND hDlg)
{
    WCHAR szBuffer[BUFFER_SIZE];
    HWND hDlgCtrl;
    FILE * file;
    UINT length;
    LRESULT pos;
    HRESULT hr;

    hr = StringCbCopyW(szBuffer, sizeof(szBuffer), szDrive);
    if (FAILED(hr))
        return FALSE;

    hr = StringCbCatW(szBuffer, sizeof(szBuffer), L"freeldr.ini");
    if (FAILED(hr))
        return FALSE;

    file = _wfopen(szBuffer, L"rt");
    if (!file)
    {
        hr = StringCbCopyW(szBuffer, sizeof(szBuffer), szDrive);
        if (FAILED(hr))
            return FALSE;

        hr = StringCbCatW(szBuffer, sizeof(szBuffer), L"boot.ini");
        if (FAILED(hr))
            return FALSE;
            
        file = _wfopen(szBuffer, L"rt");
        if (!file)
            return FALSE;
    }     

    hDlgCtrl = GetDlgItem(hDlg, IDC_LIST_BOX);

    while(!feof(file))
    {
        if (fgetws(szBuffer, BUFFER_SIZE, file))
        {
            length = wcslen(szBuffer);
            if (length > 1)
            {
                szBuffer[length] = L'\0';
                szBuffer[length - 1] = L'\0';

                pos = SendMessageW(hDlgCtrl, LB_ADDSTRING, 0, (LPARAM)szBuffer);

                if (szBuffer[0] == L'[')
                    continue;

                if (!_wcsnicmp(szBuffer, L"timeout=", 8))
                {
                    Settings.TimeOut = _wtoi(&szBuffer[8]);
                    continue;
                }

                if (!_wcsnicmp(szBuffer, L"default=", 8))
                {
                    wcscpy(Settings.szDefaultOS, &szBuffer[8]);
                    continue;
                }
                if (pos != LB_ERR)
                    SendMessage(hDlgCtrl, LB_SETITEMDATA, pos, 1); // indicate that this item is an boot entry
                Settings.OSConfigurationCount++;
            }
        }
    }

    fclose(file);
    Settings.UseBootIni = TRUE;

    pos = SendMessageW(hDlgCtrl, LB_FINDSTRING, 3, (LPARAM)Settings.szDefaultOS);
    if (pos != LB_ERR)
    {
       Settings.szDefaultPos = pos;
       SendMessage(hDlgCtrl, LB_SETCURSEL, pos, 0);
    }

    SetDlgItemInt(hDlg, IDC_TXT_BOOT_TIMEOUT, Settings.TimeOut, FALSE);
    if (Settings.OSConfigurationCount < 2)
    {
        EnableWindow(GetDlgItem(hDlg, IDC_BTN_SET_DEFAULT_BOOT), FALSE);
        EnableWindow(GetDlgItem(hDlg, IDC_BTN_MOVE_UP_BOOT_OPTION), FALSE);
        EnableWindow(GetDlgItem(hDlg, IDC_BTN_MOVE_DOWN_BOOT_OPTION), FALSE);
    }
    return TRUE;
}