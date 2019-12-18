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
typedef  int /*<<< orphan*/  szVer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetRegValue (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static 
BOOL
GetDirectXVersion(WCHAR * szBuffer)
{
    WCHAR szVer[20];

    if (!GetRegValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\DirectX", L"Version", REG_SZ, szVer, sizeof(szVer)))
        return FALSE;

    if(!wcscmp(szVer, L"4.02.0095"))
        wcscpy(szBuffer, L"1.0");
    else if (!wcscmp(szVer, L"4.03.00.1096"))
        wcscpy(szBuffer, L"2.0");
    else if (!wcscmp(szVer, L"4.04.0068"))
        wcscpy(szBuffer, L"3.0");
    else if (!wcscmp(szVer, L"4.04.0069"))
        wcscpy(szBuffer, L"3.0");
    else if (!wcscmp(szVer, L"4.05.00.0155"))
        wcscpy(szBuffer, L"5.0");
    else if (!wcscmp(szVer, L"4.05.01.1721"))
        wcscpy(szBuffer, L"5.0");
    else if (!wcscmp(szVer, L"4.05.01.1998"))
        wcscpy(szBuffer, L"5.0");
    else if (!wcscmp(szVer, L"4.06.02.0436"))
        wcscpy(szBuffer, L"6.0");
    else if (!wcscmp(szVer, L"4.07.00.0700"))
        wcscpy(szBuffer, L"7.0");
    else if (!wcscmp(szVer, L"4.07.00.0716"))
        wcscpy(szBuffer, L"7.0a");
    else if (!wcscmp(szVer, L"4.08.00.0400"))
        wcscpy(szBuffer, L"8.0");
    else if (!wcscmp(szVer, L"4.08.01.0881"))
        wcscpy(szBuffer, L"8.1");
    else if (!wcscmp(szVer, L"4.08.01.0810"))
        wcscpy(szBuffer, L"8.1");
    else if (!wcscmp(szVer, L"4.09.0000.0900"))
        wcscpy(szBuffer, L"9.0");
    else if (!wcscmp(szVer, L"4.09.00.0900"))
        wcscpy(szBuffer, L"9.0");
    else if (!wcscmp(szVer, L"4.09.0000.0901"))
        wcscpy(szBuffer, L"9.0a");
    else if (!wcscmp(szVer, L"4.09.00.0901"))
        wcscpy(szBuffer, L"9.0a");
    else if (!wcscmp(szVer, L"4.09.0000.0902"))
        wcscpy(szBuffer, L"9.0b");
    else if (!wcscmp(szVer, L"4.09.00.0902"))
        wcscpy(szBuffer, L"9.0b");
    else if (!wcscmp(szVer, L"4.09.00.0904"))
        wcscpy(szBuffer, L"9.0c");
    else if (!wcscmp(szVer, L"4.09.0000.0904"))
        wcscpy(szBuffer, L"9.0c");
    else
        return FALSE;

    return TRUE;
}