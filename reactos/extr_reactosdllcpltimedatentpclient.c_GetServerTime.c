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
typedef  int /*<<< orphan*/  ULONG ;
typedef  scalar_t__ PINFO ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  INFO ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DestroyConnection () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ InitConnection (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ReceiveData (scalar_t__) ; 
 scalar_t__ SendData (scalar_t__) ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

ULONG
GetServerTime(LPWSTR lpAddress)
{
    PINFO pInfo;
    LPSTR lpAddr;
    DWORD dwSize = wcslen(lpAddress) + 1;
    ULONG ulTime = 0;

    pInfo = (PINFO)HeapAlloc(GetProcessHeap(),
                             0,
                             sizeof(INFO));
    lpAddr = (LPSTR)HeapAlloc(GetProcessHeap(),
                              0,
                              dwSize);

    if (pInfo && lpAddr)
    {
        if (WideCharToMultiByte(CP_ACP,
                                0,
                                lpAddress,
                                -1,
                                lpAddr,
                                dwSize,
                                NULL,
                                NULL))
        {
            if (InitConnection(pInfo, lpAddr))
            {
                if (SendData(pInfo))
                {
                    ulTime = ReceiveData(pInfo);
                }
            }

            DestroyConnection();
        }
    }

    if (pInfo)
        HeapFree(GetProcessHeap(), 0, pInfo);
    if (lpAddr)
        HeapFree(GetProcessHeap(), 0, lpAddr);

    return ulTime;
}