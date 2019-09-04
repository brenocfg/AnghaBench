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
typedef  int WCHAR ;
typedef  int UINT ;
typedef  int* LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HMENU ;

/* Variables and functions */
 scalar_t__ GetMenu (int /*<<< orphan*/ ) ; 
 scalar_t__ LoadStringW (int /*<<< orphan*/ ,int,int*,int) ; 
 int MF_POPUP ; 
 int /*<<< orphan*/  SB_SETTEXTW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hStatusBar ; 
 int* wcschr (int*,int) ; 
 int /*<<< orphan*/  wcscpy (int*,char*) ; 

__attribute__((used)) static void OnMenuSelect(HWND hWnd, UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
    WCHAR str[100];

    wcscpy(str, L"");
    if (nFlags & MF_POPUP)
    {
        if (hSysMenu != GetMenu(hWnd))
        {
            if (nItemID == 2) nItemID = 5;
        }
    }
    if (LoadStringW(hInst, nItemID, str, 100))
    {
        /* load appropriate string*/
        LPWSTR lpsz = str;
        /* first newline terminates actual string*/
        lpsz = wcschr(lpsz, L'\n');
        if (lpsz != NULL)
            *lpsz = L'\0';
    }
    SendMessageW(hStatusBar, SB_SETTEXTW, 0, (LPARAM)str);
}