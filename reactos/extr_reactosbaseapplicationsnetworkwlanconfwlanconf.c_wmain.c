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
typedef  int /*<<< orphan*/  IP_ADAPTER_INDEX_MAP ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoFormatMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IDS_NO_WLAN_ADAPTER ; 
 int /*<<< orphan*/  OpenWlanAdapter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseCmdline (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  WlanConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WlanDisconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WlanPrintCurrentStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WlanScan (int /*<<< orphan*/ ) ; 
 scalar_t__ bConnect ; 
 scalar_t__ bDisconnect ; 
 scalar_t__ bScan ; 

int wmain(int argc, WCHAR *argv[])
{
    HANDLE hAdapter;
    IP_ADAPTER_INDEX_MAP IpInfo;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    if (!ParseCmdline(argc, argv))
        return -1;

    if (!OpenWlanAdapter(&hAdapter, &IpInfo))
    {
        ConResPuts(StdOut, IDS_NO_WLAN_ADAPTER);
        return -1;
    }

    if (bScan)
    {
        if (!WlanScan(hAdapter))
        {
            DoFormatMessage(GetLastError());
            CloseHandle(hAdapter);
            return -1;
        }
    }
    else if (bDisconnect)
    {
        if (!WlanDisconnect(hAdapter, &IpInfo))
        {
            DoFormatMessage(GetLastError());
            CloseHandle(hAdapter);
            return -1;
        }
    }
    else if (bConnect)
    {
        if (!WlanConnect(hAdapter))
        {
            DoFormatMessage(GetLastError());
            CloseHandle(hAdapter);
            return -1;
        }
    }
    else
    {
        if (!WlanPrintCurrentStatus(hAdapter))
        {
            DoFormatMessage(GetLastError());
            CloseHandle(hAdapter);
            return -1;
        }
    }

    CloseHandle(hAdapter);
    return 0;
}