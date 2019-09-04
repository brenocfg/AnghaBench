#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int OSConfigurationCount; int /*<<< orphan*/  TimeOut; scalar_t__ szDefaultPos; int /*<<< orphan*/  szDefaultOS; int /*<<< orphan*/  UseBootIni; } ;
struct TYPE_4__ {scalar_t__ cx; } ;
typedef  int SIZE_T ;
typedef  TYPE_1__ SIZE ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ExpandEnvironmentStringsW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,int*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_BTN_MOVE_DOWN_BOOT_OPTION ; 
 int /*<<< orphan*/  IDC_BTN_MOVE_UP_BOOT_OPTION ; 
 int /*<<< orphan*/  IDC_BTN_SET_DEFAULT_BOOT ; 
 int /*<<< orphan*/  IDC_LIST_BOX ; 
 int /*<<< orphan*/  IDC_TXT_BOOT_TIMEOUT ; 
 scalar_t__ LB_ERR ; 
 scalar_t__ ListBox_AddString (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ListBox_FindString (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ListBox_GetHorizontalExtent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListBox_SetCurSel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ListBox_SetHorizontalExtent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ListBox_SetItemData (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ MemAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ Settings ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_GETFONT ; 
 int /*<<< orphan*/  _SH_DENYWR ; 
 int /*<<< orphan*/  _wcsnicmp (int*,char*,int) ; 
 int /*<<< orphan*/ * _wfsopen (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wtoi (int*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgetws (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int*) ; 
 int wcslen (int*) ; 

__attribute__((used)) static BOOL
LoadIniFile(HWND hDlg,
            LPCWSTR lpszIniFile)
{
    DWORD  dwNumOfChars;
    LPWSTR lpszFileName;
    FILE*  file;

    WCHAR szBuffer[512];
    HWND hDlgCtrl;
    SIZE_T length;
    LRESULT pos;

    SIZE size;
    LONG horzExt;

    HDC hDC;
    HFONT hFont, hOldFont;

    /*
     * Open for read + write (without file creation if it didn't already exist)
     * of a read-only text stream.
     */
    dwNumOfChars = ExpandEnvironmentStringsW(lpszIniFile, NULL, 0);
    lpszFileName = (LPWSTR)MemAlloc(0, dwNumOfChars * sizeof(WCHAR));
    ExpandEnvironmentStringsW(lpszIniFile, lpszFileName, dwNumOfChars);

    file = _wfsopen(lpszFileName, L"rt", _SH_DENYWR); // r+t <-- read write text ; rt <-- read text
    MemFree(lpszFileName);

    if (!file) return FALSE;

    hDlgCtrl = GetDlgItem(hDlg, IDC_LIST_BOX);

    hDC      = GetDC(hDlgCtrl);
    hFont    = (HFONT)SendMessageW(hDlgCtrl, WM_GETFONT, 0, 0);
    hOldFont = (HFONT)SelectObject(hDC, hFont);

    while (!feof(file) && fgetws(szBuffer, ARRAYSIZE(szBuffer), file))
    {
        length = wcslen(szBuffer);
        if (length > 1)
        {
            /* Remove \r\n */
            szBuffer[length-1] = szBuffer[length] = L'\0';

            pos = ListBox_AddString(hDlgCtrl, szBuffer);

            GetTextExtentPoint32W(hDC, szBuffer, (int)wcslen(szBuffer), &size);
            horzExt = max((LONG)ListBox_GetHorizontalExtent(hDlgCtrl), size.cx + 5); // 5 to have a little room between the text and the end of the list box.
            ListBox_SetHorizontalExtent(hDlgCtrl, horzExt);

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
                ListBox_SetItemData(hDlgCtrl, pos, 1); // indicate that this item is a boot entry

            Settings.OSConfigurationCount++;
        }
    }

    SelectObject(hDC, hOldFont);
    ReleaseDC(hDlgCtrl, hDC);

    fclose(file);
    Settings.UseBootIni = TRUE;

    /*
     * Start to search for the string at the "operating systems" section
     * (after the "boot loader" section, which takes 3 lines in the .INI file).
     */
    pos = ListBox_FindString(hDlgCtrl, 3, Settings.szDefaultOS);
    if (pos != LB_ERR)
    {
        Settings.szDefaultPos = (ULONG)pos;
        ListBox_SetCurSel(hDlgCtrl, pos);
        // SendMessageW(hDlgCtrl, WM_VSCROLL, SB_LINEDOWN, 0); // Or use SetScroll...()
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