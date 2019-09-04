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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FORMAT_MESSAGE_ALLOCATE_BUFFER ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int /*<<< orphan*/  FormatMessageW (int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LANG_USER_DEFAULT ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void ShowLastWin32Error(HWND hwndParent)
{
    DWORD dwError;
    LPWSTR lpMsgBuf = NULL;

    dwError = GetLastError();
    if (dwError == ERROR_SUCCESS)
        return;

    if (!FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM |
                        FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        dwError,
                        LANG_USER_DEFAULT,
                        (LPWSTR)&lpMsgBuf,
                        0, NULL))
    {
        return;
    }

    MessageBoxW(hwndParent, lpMsgBuf, NULL, MB_OK | MB_ICONERROR);
    LocalFree(lpMsgBuf);
}