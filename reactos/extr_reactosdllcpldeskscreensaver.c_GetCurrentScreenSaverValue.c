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
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static LPTSTR
GetCurrentScreenSaverValue(LPTSTR lpValue)
{
    HKEY hKey;
    LPTSTR lpBuf = NULL;
    DWORD BufSize, Type = REG_SZ;
    LONG Ret;

    Ret = RegOpenKeyEx(HKEY_CURRENT_USER,
                       _T("Control Panel\\Desktop"),
                       0,
                       KEY_READ,
                       &hKey);
    if (Ret != ERROR_SUCCESS)
        return NULL;

    Ret = RegQueryValueEx(hKey,
                          lpValue,
                          0,
                          &Type,
                          NULL,
                          &BufSize);
    if (Ret == ERROR_SUCCESS)
    {
        lpBuf = HeapAlloc(GetProcessHeap(),
                          0,
                          BufSize);
        if (lpBuf)
        {
            Ret = RegQueryValueEx(hKey,
                                  lpValue,
                                  0,
                                  &Type,
                                  (LPBYTE)lpBuf,
                                  &BufSize);
            if (Ret != ERROR_SUCCESS)
            {
                HeapFree(GetProcessHeap(), 0, lpBuf);
                lpBuf = NULL;
            }
        }
    }

    RegCloseKey(hKey);

    return lpBuf;
}