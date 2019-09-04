#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
struct TYPE_5__ {int Ttl; } ;
struct TYPE_4__ {scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int Address ; 
 scalar_t__* CanonName ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ConsoleCtrlHandler ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ Family ; 
 int /*<<< orphan*/  FreeAddrInfoW (TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IDS_PINGING_ADDRESS ; 
 int /*<<< orphan*/  IDS_PINGING_HOSTNAME ; 
 int /*<<< orphan*/  IDS_PING_SIZE ; 
 int /*<<< orphan*/  IDS_WINSOCK_FAIL ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ Icmp6CreateFile () ; 
 int /*<<< orphan*/  IcmpCloseHandle (scalar_t__) ; 
 scalar_t__ IcmpCreateFile () ; 
 TYPE_2__ IpOptions ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  ParseCmdLine (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Ping () ; 
 int PingCount ; 
 int /*<<< orphan*/  PingForever ; 
 int /*<<< orphan*/  PrintStats () ; 
 int RequestSize ; 
 int /*<<< orphan*/  ResolveTarget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetConsoleCtrlHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* Target ; 
 int /*<<< orphan*/  TargetName ; 
 scalar_t__ WSAAddressToStringW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hIcmpFile ; 

int
wmain(int argc, WCHAR *argv[])
{
    WSADATA wsaData;
    ULONG i;
    DWORD StrLen = 46;
    int Status;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    IpOptions.Ttl = 128;

    if (!ParseCmdLine(argc, argv))
        return 1;

    if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE))
    {
        DPRINT("Failed to set control handler: %lu\n", GetLastError());
        return 1;
    }

    Status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (Status != 0)
    {
        ConResPrintf(StdErr, IDS_WINSOCK_FAIL, Status);
        return 1;
    }

    if (!ResolveTarget(TargetName))
    {
        WSACleanup();
        return 1;
    }

    if (WSAAddressToStringW(Target->ai_addr, (DWORD)Target->ai_addrlen, NULL, Address, &StrLen) != 0)
    {
        DPRINT("WSAAddressToStringW failed: %d\n", WSAGetLastError());
        FreeAddrInfoW(Target);
        WSACleanup();
        return 1;
    }

    if (Family == AF_INET6)
        hIcmpFile = Icmp6CreateFile();
    else
        hIcmpFile = IcmpCreateFile();


    if (hIcmpFile == INVALID_HANDLE_VALUE)
    {
        DPRINT("IcmpCreateFile failed: %lu\n", GetLastError());
        FreeAddrInfoW(Target);
        WSACleanup();
        return 1;
    }

    if (*CanonName)
        ConResPrintf(StdOut, IDS_PINGING_HOSTNAME, CanonName, Address);
    else
        ConResPrintf(StdOut, IDS_PINGING_ADDRESS, Address);

    ConResPrintf(StdOut, IDS_PING_SIZE, RequestSize);

    Ping();

    i = 1;
    while (i < PingCount)
    {
        Sleep(1000);
        Ping();

        if (!PingForever)
            i++;
    }

    PrintStats();

    IcmpCloseHandle(hIcmpFile);
    FreeAddrInfoW(Target);
    WSACleanup();

    return 0;
}