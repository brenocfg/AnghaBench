#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ dwNumEntries; TYPE_1__* table; } ;
struct TYPE_5__ {size_t dwState; char* dwOwningPid; int /*<<< orphan*/  dwRemotePort; int /*<<< orphan*/  dwRemoteAddr; int /*<<< orphan*/  dwLocalPort; int /*<<< orphan*/  dwLocalAddr; } ;
typedef  TYPE_2__* PMIB_TCPTABLE_OWNER_PID ;
typedef  int /*<<< orphan*/  MIB_TCPTABLE_OWNER_PID ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ADDRESSLEN ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DoFormatMessage (scalar_t__) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetExtendedTcpTable (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIpHostName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetPortName (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HOSTNAMELEN ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t MIB_TCP_STATE_CLOSE_WAIT ; 
 size_t MIB_TCP_STATE_ESTAB ; 
 size_t MIB_TCP_STATE_LISTEN ; 
 size_t MIB_TCP_STATE_TIME_WAIT ; 
 scalar_t__ NO_ERROR ; 
 int PORTNAMELEN ; 
 int /*<<< orphan*/  TCP_TABLE_OWNER_PID_ALL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * TcpState ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bDoShowAllCons ; 
 scalar_t__ bDoShowProcessId ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 

VOID ShowTcpTable()
{
    PMIB_TCPTABLE_OWNER_PID tcpTable;
    DWORD error, dwSize;
    DWORD i;
    CHAR HostIp[HOSTNAMELEN], HostPort[PORTNAMELEN];
    CHAR RemoteIp[HOSTNAMELEN], RemotePort[PORTNAMELEN];
    CHAR Host[ADDRESSLEN];
    CHAR Remote[ADDRESSLEN];
    CHAR PID[64];

    /* Get the table of TCP endpoints */
    dwSize = sizeof (MIB_TCPTABLE_OWNER_PID);
    /* Should also work when we get new connections between 2 GetTcpTable()
     * calls: */
    do
    {
        tcpTable = (PMIB_TCPTABLE_OWNER_PID) HeapAlloc(GetProcessHeap(), 0, dwSize);
        error = GetExtendedTcpTable(tcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
        if ( error != NO_ERROR )
            HeapFree(GetProcessHeap(), 0, tcpTable);
    }
    while  ( error == ERROR_INSUFFICIENT_BUFFER );

    if (error != NO_ERROR)
    {
        printf("Failed to snapshot TCP endpoints.\n");
        DoFormatMessage(error);
        exit(EXIT_FAILURE);
    }

    /* Dump the TCP table */
    for (i = 0; i < tcpTable->dwNumEntries; i++)
    {
        /* If we aren't showing all connections, only display established, close wait
         * and time wait. This is the default output for netstat */
        if (bDoShowAllCons || (tcpTable->table[i].dwState ==  MIB_TCP_STATE_ESTAB)
            || (tcpTable->table[i].dwState ==  MIB_TCP_STATE_CLOSE_WAIT)
            || (tcpTable->table[i].dwState ==  MIB_TCP_STATE_TIME_WAIT))
        {
            /* I've split this up so it's easier to follow */
            GetIpHostName(TRUE, tcpTable->table[i].dwLocalAddr, HostIp, HOSTNAMELEN);
            GetPortName(tcpTable->table[i].dwLocalPort, "tcp", HostPort, PORTNAMELEN);
            sprintf(Host, "%s:%s", HostIp, HostPort);

            if (tcpTable->table[i].dwState ==  MIB_TCP_STATE_LISTEN)
            {
                sprintf(Remote, "%s:0", HostIp);
            }
            else
            {
                GetIpHostName(FALSE, tcpTable->table[i].dwRemoteAddr, RemoteIp, HOSTNAMELEN);
                GetPortName(tcpTable->table[i].dwRemotePort, "tcp", RemotePort, PORTNAMELEN);
                sprintf(Remote, "%s:%s", RemoteIp, RemotePort);
            }

            if (bDoShowProcessId)
            {
                sprintf(PID, "%ld", tcpTable->table[i].dwOwningPid);
            }
            else
            {
                PID[0] = 0;
            }

            _tprintf(_T("  %-6s %-22s %-22s %-11s %s\n"), _T("TCP"),
            Host, Remote, TcpState[tcpTable->table[i].dwState], PID);
        }
    }
    HeapFree(GetProcessHeap(), 0, tcpTable);
}