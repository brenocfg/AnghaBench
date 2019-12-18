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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int GetEnvironmentVariableW (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 

__attribute__((used)) static DWORD
GetSystemDrive(WCHAR **szSystemDrive)
{
    DWORD dwBufSize;

    /* Get Path to freeldr.ini or boot.ini */
    *szSystemDrive = HeapAlloc(GetProcessHeap(), 0, MAX_PATH * sizeof(WCHAR));
    if (*szSystemDrive != NULL)
    {
        dwBufSize = GetEnvironmentVariableW(L"SystemDrive", *szSystemDrive, MAX_PATH);
        if (dwBufSize > MAX_PATH)
        {
            WCHAR *szTmp;
            DWORD dwBufSize2;

            szTmp = HeapReAlloc(GetProcessHeap(), 0, *szSystemDrive, dwBufSize * sizeof(WCHAR));
            if (szTmp == NULL)
                goto FailGetSysDrive;

            *szSystemDrive = szTmp;

            dwBufSize2 = GetEnvironmentVariableW(L"SystemDrive", *szSystemDrive, dwBufSize);
            if (dwBufSize2 > dwBufSize || dwBufSize2 == 0)
                goto FailGetSysDrive;
        }
        else if (dwBufSize == 0)
        {
FailGetSysDrive:
            HeapFree(GetProcessHeap(), 0, *szSystemDrive);
            *szSystemDrive = NULL;
            return 0;
        }

        return dwBufSize;
    }

    return 0;
}