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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int WCHAR ;
typedef  int* PWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int* FindDateSep (int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IDC_SHRTDATEFMT_COMBO ; 
 int /*<<< orphan*/  IDC_SHRTDATESEP_COMBO ; 
 int /*<<< orphan*/  IDS_ERROR_SYMBOL_FORMAT_SHORT ; 
 int MAX_SAMPLES_STR_SIZE ; 
 int /*<<< orphan*/  PrintErrorMsgBox (int /*<<< orphan*/ ) ; 
 int* ReplaceSubStr (int*,int*,int*) ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  isDateCompAl (int) ; 
 scalar_t__ iswalnum (int) ; 
 int /*<<< orphan*/  wcscpy (int*,int*) ; 
 size_t wcslen (int*) ; 

__attribute__((used)) static BOOL
SetShortDateFormat(HWND hwndDlg, PWSTR pszShortDateFmt)
{
    WCHAR szShortDateSep[MAX_SAMPLES_STR_SIZE];
    WCHAR szFoundDateSep[MAX_SAMPLES_STR_SIZE];
    PWSTR pszResultStr;
    PWSTR pszFoundSep;
    BOOL OpenApostFlg = FALSE;
    INT nFmtStrSize;
    INT nDateCompCount;

    /* Get format */
    SendDlgItemMessageW(hwndDlg, IDC_SHRTDATEFMT_COMBO,
                        WM_GETTEXT,
                        (WPARAM)MAX_SAMPLES_STR_SIZE,
                        (LPARAM)pszShortDateFmt);

    /* Get separator */
    SendDlgItemMessageW(hwndDlg, IDC_SHRTDATESEP_COMBO,
                        WM_GETTEXT,
                        (WPARAM)MAX_SAMPLES_STR_SIZE,
                        (LPARAM)szShortDateSep);

    /* Get format-string size */
    nFmtStrSize = wcslen(pszShortDateFmt);

    /* Check date components */
    for (nDateCompCount = 0; nDateCompCount < nFmtStrSize; nDateCompCount++)
    {
        if (pszShortDateFmt[nDateCompCount] == L'\'')
        {
            OpenApostFlg = !OpenApostFlg;
        }

        if (iswalnum(pszShortDateFmt[nDateCompCount]) &&
            !isDateCompAl(pszShortDateFmt[nDateCompCount]) &&
            !OpenApostFlg)
        {
            PrintErrorMsgBox(IDS_ERROR_SYMBOL_FORMAT_SHORT);
            return FALSE;
        }
    }

    if (OpenApostFlg || nFmtStrSize == 0)
    {
        PrintErrorMsgBox(IDS_ERROR_SYMBOL_FORMAT_SHORT);
        return FALSE;
    }

    pszFoundSep = FindDateSep(pszShortDateFmt);
    if (pszFoundSep != NULL)
    {
        /* Substring replacement of separator */
        wcscpy(szFoundDateSep, pszFoundSep);
        pszResultStr = ReplaceSubStr(pszShortDateFmt, szShortDateSep, szFoundDateSep);
        if (pszResultStr != NULL)
        {
            wcscpy(pszShortDateFmt, pszResultStr);
            HeapFree(GetProcessHeap(), 0, pszResultStr);
        }

        HeapFree(GetProcessHeap(), 0, pszFoundSep);
    }

    return TRUE;
}