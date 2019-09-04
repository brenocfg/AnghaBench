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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayTableHeader () ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
#define  ICMP 131 
#define  IP 130 
 int Protocol ; 
 int /*<<< orphan*/  ShowEthernetStatistics () ; 
 int /*<<< orphan*/  ShowIcmpStatistics () ; 
 int /*<<< orphan*/  ShowIpStatistics () ; 
 int /*<<< orphan*/  ShowTcpStatistics () ; 
 int /*<<< orphan*/  ShowTcpTable () ; 
 int /*<<< orphan*/  ShowUdpStatistics () ; 
 int /*<<< orphan*/  ShowUdpTable () ; 
#define  TCP 129 
#define  UDP 128 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 scalar_t__ bDoShowAllCons ; 
 scalar_t__ bDoShowEthStats ; 
 scalar_t__ bDoShowProtoCons ; 
 scalar_t__ bDoShowProtoStats ; 
 scalar_t__ bDoShowRouteTable ; 
 scalar_t__ bNoOptions ; 
 int system (char*) ; 

BOOL DisplayOutput()
{
    if (bNoOptions)
    {
        DisplayTableHeader();
        ShowTcpTable();
        return EXIT_SUCCESS;
    }

    if (bDoShowRouteTable)
    {
        /* mingw doesn't have lib for _tsystem */
        if (system("route print") == -1)
        {
            _tprintf(_T("cannot find 'route.exe'\n"));
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (bDoShowEthStats)
    {
        ShowEthernetStatistics();
        return EXIT_SUCCESS;
    }

    if (bDoShowProtoCons)
    {
        switch (Protocol)
        {
                case IP :
                    if (bDoShowProtoStats)
                    {
                        ShowIpStatistics();
                        return EXIT_SUCCESS;
                    }
                    break;
                case ICMP :
                    if (bDoShowProtoStats)
                    {
                        ShowIcmpStatistics();
                        return EXIT_SUCCESS;
                    }
                    break;
                case TCP :
                    if (bDoShowProtoStats)
                        ShowTcpStatistics();
                    _tprintf(_T("\nActive Connections\n"));
                    DisplayTableHeader();
                    ShowTcpTable();
                    break;
                case UDP :
                    if (bDoShowProtoStats)
                        ShowUdpStatistics();
                    _tprintf(_T("\nActive Connections\n"));
                    DisplayTableHeader();
                    ShowUdpTable();
                    break;
                default :
                    break;
        }
    }
    else if (bDoShowProtoStats)
    {
        ShowIpStatistics();
        ShowIcmpStatistics();
        ShowTcpStatistics();
        ShowUdpStatistics();
        return EXIT_SUCCESS;
    }
    else
    {
        _tprintf(_T("\nActive Connections\n"));
        DisplayTableHeader();
        ShowTcpTable();
        if (bDoShowAllCons)
            ShowUdpTable();
    }
    return EXIT_SUCCESS;
}