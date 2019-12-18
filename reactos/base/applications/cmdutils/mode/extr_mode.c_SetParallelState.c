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
typedef  char* INT ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DDD_REMOVE_DEFINITION ; 
 int /*<<< orphan*/  DefineDosDeviceW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PORTNAME_LEN ; 
 int /*<<< orphan*/  ShowParallelStatus (char*) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

int SetParallelState(INT nPortNum)
{
    WCHAR szPortName[MAX_PORTNAME_LEN];
    WCHAR szTargetPath[MAX_PORTNAME_LEN];

    swprintf(szPortName, L"LPT%d", nPortNum);
    swprintf(szTargetPath, L"COM%d", nPortNum);
    if (!DefineDosDeviceW(DDD_REMOVE_DEFINITION, szPortName, szTargetPath))
    {
        ConPrintf(StdErr, L"ERROR: SetParallelState(%d) - DefineDosDevice(%s) failed: 0x%lx\n", nPortNum, szPortName, GetLastError());
    }

    ShowParallelStatus(nPortNum);
    return 0;
}