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
typedef  int /*<<< orphan*/ * PWLX_NOTIFY_HANDLER ;
typedef  int /*<<< orphan*/  PSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 

PWLX_NOTIFY_HANDLER
GetNotificationHandler(
    HKEY hDllKey,
    HINSTANCE hInstance,
    PSTR pNotification)
{
    CHAR szFuncBuffer[128];
    DWORD dwSize;
    DWORD dwType;
    LONG lError;

    dwSize = 128;
    lError = RegQueryValueExA(hDllKey,
                              pNotification,
                              NULL,
                              &dwType,
                              (PBYTE)szFuncBuffer,
                              &dwSize);
    if (lError == ERROR_SUCCESS)
    {
        return (PWLX_NOTIFY_HANDLER)GetProcAddress(hInstance, szFuncBuffer);
    }

    return NULL;
}