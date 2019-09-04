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
struct TYPE_5__ {int /*<<< orphan*/  dwOwningPid; int /*<<< orphan*/  dwLocalPort; int /*<<< orphan*/  dwLocalAddr; } ;
typedef  TYPE_2__* PMIB_UDPTABLE_OWNER_PID ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int ADDRESSLEN ; 
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DoFormatMessage (scalar_t__) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ GetExtendedUdpTable (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIpHostName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  GetPortName (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HOSTNAMELEN ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int PORTNAMELEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UDP_TABLE_OWNER_PID ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bDoShowProcessId ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 

VOID ShowUdpTable()
{
    PMIB_UDPTABLE_OWNER_PID udpTable;
    DWORD error, dwSize;
    DWORD i;
    CHAR HostIp[HOSTNAMELEN], HostPort[PORTNAMELEN];
    CHAR Host[ADDRESSLEN];
    CHAR PID[64];

    /* Get the table of UDP endpoints */
    dwSize = 0;
    error = GetExtendedUdpTable(NULL, &dwSize, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0);
    if (error != ERROR_INSUFFICIENT_BUFFER)
    {
        printf("Failed to snapshot UDP endpoints.\n");
        DoFormatMessage(error);
        exit(EXIT_FAILURE);
    }
    udpTable = (PMIB_UDPTABLE_OWNER_PID) HeapAlloc(GetProcessHeap(), 0, dwSize);
    error = GetExtendedUdpTable(udpTable, &dwSize, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0);
    if (error)
    {
        printf("Failed to snapshot UDP endpoints table.\n");
        DoFormatMessage(error);
        HeapFree(GetProcessHeap(), 0, udpTable);
        exit(EXIT_FAILURE);
    }

    /* Dump the UDP table */
    for (i = 0; i < udpTable->dwNumEntries; i++)
    {

        /* I've split this up so it's easier to follow */
        GetIpHostName(TRUE, udpTable->table[i].dwLocalAddr, HostIp, HOSTNAMELEN);
        GetPortName(udpTable->table[i].dwLocalPort, "tcp", HostPort, PORTNAMELEN);

        sprintf(Host, "%s:%s", HostIp, HostPort);

        if (bDoShowProcessId)
        {
            sprintf(PID, "%ld", udpTable->table[i].dwOwningPid);
        }
        else
        {
            PID[0] = 0;
        }

        _tprintf(_T("  %-6s %-22s %-34s %s\n"), _T("UDP"), Host,  _T("*:*"), PID);
    }

    HeapFree(GetProcessHeap(), 0, udpTable);
}