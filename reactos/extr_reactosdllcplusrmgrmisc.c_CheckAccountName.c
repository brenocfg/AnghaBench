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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _tcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _tcspbrk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL
CheckAccountName(HWND hwndDlg,
                 INT nIdDlgItem,
                 LPTSTR lpAccountName)
{
    TCHAR szAccountName[256];
    UINT uLen;

    if (lpAccountName)
        uLen = _tcslen(lpAccountName);
    else
        uLen = GetDlgItemText(hwndDlg, nIdDlgItem, szAccountName, 256);

    /* Check the account name */
    if (uLen > 0 &&
        _tcspbrk((lpAccountName) ? lpAccountName : szAccountName, TEXT("\"*+,/\\:;<=>?[]|")) != NULL)
    {
        MessageBox(hwndDlg,
                   TEXT("The account name you entered is invalid! An account name must not contain the following characters: *+,/:;<=>?[\\]|"),
                   TEXT("ERROR"),
                   MB_OK | MB_ICONERROR);
        return FALSE;
    }

    return TRUE;
}