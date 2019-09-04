#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* lpLocalName; char* lpRemoteName; char* lpProvider; } ;
typedef  TYPE_1__* LPNETRESOURCE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RESOURCETYPE_DISK ; 
 int /*<<< orphan*/  RESOURCE_CONNECTED ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ WN_MORE_DATA ; 
 scalar_t__ WN_NO_MORE_ENTRIES ; 
 scalar_t__ WN_SUCCESS ; 
 int /*<<< orphan*/  WNetCloseEnum (int /*<<< orphan*/ ) ; 
 scalar_t__ WNetEnumResource (int /*<<< orphan*/ ,scalar_t__*,TYPE_1__*,scalar_t__*) ; 
 scalar_t__ WNetOpenEnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wcsicmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
DWORD
EnumerateConnections(LPCWSTR Local)
{
    DWORD dRet;
    HANDLE hEnum;
    LPNETRESOURCE lpRes;
    DWORD dSize = 0x1000;
    DWORD dCount = -1;
    LPNETRESOURCE lpCur;

    ConPrintf(StdOut, L"%s\t\t\t%s\t\t\t\t%s\n", L"Local", L"Remote", L"Provider");

    dRet = WNetOpenEnum(RESOURCE_CONNECTED, RESOURCETYPE_DISK, 0, NULL, &hEnum);
    if (dRet != WN_SUCCESS)
    {
        return 1;
    }

    lpRes = HeapAlloc(GetProcessHeap(), 0, dSize);
    if (!lpRes)
    {
        WNetCloseEnum(hEnum);
        return 1;
    }

    do
    {
        dSize = 0x1000;
        dCount = -1;

        memset(lpRes, 0, dSize);
        dRet = WNetEnumResource(hEnum, &dCount, lpRes, &dSize);
        if (dRet == WN_SUCCESS || dRet == WN_MORE_DATA)
        {
            lpCur = lpRes;
            for (; dCount; dCount--)
            {
                if (!Local || wcsicmp(lpCur->lpLocalName, Local) == 0)
                {
                    ConPrintf(StdOut, L"%s\t\t\t%s\t\t%s\n", lpCur->lpLocalName, lpCur->lpRemoteName, lpCur->lpProvider);
                }

                lpCur++;
            }
        }
    } while (dRet != WN_NO_MORE_ENTRIES);

    HeapFree(GetProcessHeap(), 0, lpRes);
    WNetCloseEnum(hEnum);

    return 0;
}