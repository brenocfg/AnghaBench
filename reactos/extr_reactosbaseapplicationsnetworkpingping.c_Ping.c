#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  S_addr; } ;
struct TYPE_18__ {TYPE_4__ S_un; } ;
struct TYPE_15__ {int /*<<< orphan*/  Word; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
struct sockaddr_in6 {TYPE_5__ sin_addr; int /*<<< orphan*/  sin_family; TYPE_3__ sin6_addr; scalar_t__ sin6_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_19__ {int Ttl; } ;
struct TYPE_22__ {int Status; int DataSize; int RoundTripTime; TYPE_6__ Options; int /*<<< orphan*/  Address; } ;
struct TYPE_21__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_20__ {TYPE_1__ sin_addr; } ;
struct TYPE_13__ {scalar_t__ ai_addr; } ;
struct TYPE_12__ {int Status; int RoundTripTime; int /*<<< orphan*/  Address; } ;
typedef  int /*<<< orphan*/  Source ;
typedef  int /*<<< orphan*/  SockAddrIn6 ;
typedef  int /*<<< orphan*/  SockAddrIn ;
typedef  struct sockaddr_in6 SOCKADDR_IN6 ;
typedef  struct sockaddr_in6 SOCKADDR_IN ;
typedef  struct sockaddr_in6* PVOID ;
typedef  TYPE_7__* PSOCKADDR_IN ;
typedef  scalar_t__ PSOCKADDR ;
typedef  TYPE_8__* PIPV6_ADDRESS_EX ;
typedef  TYPE_9__* PICMP_ECHO_REPLY ;
typedef  TYPE_10__* PICMPV6_ECHO_REPLY ;
typedef  int /*<<< orphan*/  IPAddr ;
typedef  int /*<<< orphan*/  ICMP_ECHO_REPLY ;
typedef  int /*<<< orphan*/  ICMPV6_ECHO_REPLY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int Address ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EchosReceived ; 
 int /*<<< orphan*/  EchosSent ; 
 int /*<<< orphan*/  EchosSuccessful ; 
 scalar_t__ Family ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetNameInfoW (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_DEST_HOST_UNREACHABLE ; 
 int /*<<< orphan*/  IDS_DEST_NET_UNREACHABLE ; 
 int /*<<< orphan*/  IDS_NO_RESOURCES ; 
 int /*<<< orphan*/  IDS_REPLY_BYTES ; 
 int /*<<< orphan*/  IDS_REPLY_FROM ; 
 int /*<<< orphan*/  IDS_REPLY_STATUS ; 
 int /*<<< orphan*/  IDS_REPLY_TIME_0MS ; 
 int /*<<< orphan*/  IDS_REPLY_TIME_MS ; 
 int /*<<< orphan*/  IDS_REPLY_TTL ; 
 int /*<<< orphan*/  IDS_REQUEST_TIMED_OUT ; 
 int /*<<< orphan*/  IDS_TRANSMIT_FAILED ; 
 int /*<<< orphan*/  IDS_TTL_EXPIRED ; 
#define  IP_DEST_HOST_UNREACHABLE 132 
#define  IP_DEST_NET_UNREACHABLE 131 
#define  IP_REQ_TIMED_OUT 130 
#define  IP_SUCCESS 129 
#define  IP_TTL_EXPIRED_TRANSIT 128 
 int Icmp6SendEcho2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr_in6*,struct sockaddr_in6*,struct sockaddr_in6*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sockaddr_in6*,int,int /*<<< orphan*/ ) ; 
 int IcmpSendEcho2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr_in6*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sockaddr_in6*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IpOptions ; 
 int /*<<< orphan*/  NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int RTTMax ; 
 int RTTMin ; 
 int RTTTotal ; 
 int RequestSize ; 
 int SIZEOF_ICMP_ERROR ; 
 int SIZEOF_IO_STATUS_BLOCK ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 TYPE_11__* Target ; 
 int /*<<< orphan*/  Timeout ; 
 int /*<<< orphan*/  ZeroMemory (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (struct sockaddr_in6*) ; 
 int /*<<< orphan*/  hIcmpFile ; 
 struct sockaddr_in6* malloc (int) ; 

__attribute__((used)) static
void
Ping(void)
{
    PVOID ReplyBuffer = NULL;
    PVOID SendBuffer = NULL;
    DWORD ReplySize = 0;
    DWORD Status;

    SendBuffer = malloc(RequestSize);
    if (SendBuffer == NULL)
    {
        ConResPrintf(StdErr, IDS_NO_RESOURCES);
        exit(1);
    }

    ZeroMemory(SendBuffer, RequestSize);

    if (Family == AF_INET6)
        ReplySize += sizeof(ICMPV6_ECHO_REPLY);
    else
        ReplySize += sizeof(ICMP_ECHO_REPLY);

    ReplySize += RequestSize + SIZEOF_ICMP_ERROR + SIZEOF_IO_STATUS_BLOCK;

    ReplyBuffer = malloc(ReplySize);
    if (ReplyBuffer == NULL)
    {
        ConResPrintf(StdErr, IDS_NO_RESOURCES);
        free(SendBuffer);
        exit(1);
    }

    ZeroMemory(ReplyBuffer, ReplySize);

    EchosSent++;

    if (Family == AF_INET6)
    {
        struct sockaddr_in6 Source;

        ZeroMemory(&Source, sizeof(Source));
        Source.sin6_family = AF_INET6;

        Status = Icmp6SendEcho2(hIcmpFile, NULL, NULL, NULL,
                                &Source,
                                (struct sockaddr_in6 *)Target->ai_addr,
                                SendBuffer, (USHORT)RequestSize, &IpOptions,
                                ReplyBuffer, ReplySize, Timeout);
    }
    else
    {
        Status = IcmpSendEcho2(hIcmpFile, NULL, NULL, NULL,
                               ((PSOCKADDR_IN)Target->ai_addr)->sin_addr.s_addr,
                               SendBuffer, (USHORT)RequestSize, &IpOptions,
                               ReplyBuffer, ReplySize, Timeout);
    }

    free(SendBuffer);

    if (Status == 0)
    {
        Status = GetLastError();
        switch (Status)
        {
        case IP_REQ_TIMED_OUT:
            ConResPrintf(StdOut, IDS_REQUEST_TIMED_OUT);
            break;

        default:
            ConResPrintf(StdOut, IDS_TRANSMIT_FAILED, Status);
            break;
        }
    }
    else
    {
        SOCKADDR_IN6 SockAddrIn6;
        SOCKADDR_IN SockAddrIn;
        PSOCKADDR SockAddr;
        socklen_t Size;

        EchosReceived++;

        ZeroMemory(&SockAddrIn, sizeof(SockAddrIn));
        ZeroMemory(&SockAddrIn6, sizeof(SockAddrIn6));

        if (Family == AF_INET6)
        {
            PICMPV6_ECHO_REPLY pEchoReply;
            PIPV6_ADDRESS_EX Ipv6Addr;

            pEchoReply = (PICMPV6_ECHO_REPLY)ReplyBuffer;

            Ipv6Addr = (PIPV6_ADDRESS_EX)&pEchoReply->Address;
            SockAddrIn6.sin6_family = AF_INET6;
            CopyMemory(SockAddrIn6.sin6_addr.u.Word, Ipv6Addr->sin6_addr, sizeof(SockAddrIn6.sin6_addr));
            //SockAddrIn6.sin6_addr = Ipv6Addr->sin6_addr;
            SockAddr = (PSOCKADDR)&SockAddrIn6;
            Size = sizeof(SOCKADDR_IN6);

            GetNameInfoW(SockAddr,
                         Size,
                         Address,
                         NI_MAXHOST,
                         NULL,
                         0,
                         NI_NUMERICHOST);

            ConResPrintf(StdOut, IDS_REPLY_FROM, Address);

            switch (pEchoReply->Status)
            {
            case IP_SUCCESS:
            {
                EchosSuccessful++;

                if (pEchoReply->RoundTripTime == 0)
                    ConResPrintf(StdOut, IDS_REPLY_TIME_0MS);
                else
                    ConResPrintf(StdOut, IDS_REPLY_TIME_MS, pEchoReply->RoundTripTime);

                if (pEchoReply->RoundTripTime < RTTMin || RTTMin == 0)
                    RTTMin = pEchoReply->RoundTripTime;

                if (pEchoReply->RoundTripTime > RTTMax || RTTMax == 0)
                    RTTMax = pEchoReply->RoundTripTime;

                ConPuts(StdOut, L"\n");

                RTTTotal += pEchoReply->RoundTripTime;
                break;
            }

            case IP_DEST_NET_UNREACHABLE:
                ConResPrintf(StdOut, IDS_DEST_NET_UNREACHABLE);
                break;

            case IP_DEST_HOST_UNREACHABLE:
                ConResPrintf(StdOut, IDS_DEST_HOST_UNREACHABLE);
                break;

            case IP_TTL_EXPIRED_TRANSIT:
                ConResPrintf(StdOut, IDS_TTL_EXPIRED);
                break;

            default:
                ConResPrintf(StdOut, IDS_REPLY_STATUS, pEchoReply->Status);
                break;
            }
        }
        else
        {
            PICMP_ECHO_REPLY pEchoReply;
            IPAddr *IP4Addr;

            pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;

            IP4Addr = (IPAddr *)&pEchoReply->Address;
            SockAddrIn.sin_family = AF_INET;
            SockAddrIn.sin_addr.S_un.S_addr = *IP4Addr;
            SockAddr = (PSOCKADDR)&SockAddrIn;
            Size = sizeof(SOCKADDR_IN);

            GetNameInfoW(SockAddr,
                         Size,
                         Address,
                         NI_MAXHOST,
                         NULL,
                         0,
                         NI_NUMERICHOST);

            ConResPrintf(StdOut, IDS_REPLY_FROM, Address);

            switch (pEchoReply->Status)
            {
            case IP_SUCCESS:
            {
                EchosSuccessful++;

                ConResPrintf(StdOut, IDS_REPLY_BYTES, pEchoReply->DataSize);

                if (pEchoReply->RoundTripTime == 0)
                    ConResPrintf(StdOut, IDS_REPLY_TIME_0MS);
                else
                    ConResPrintf(StdOut, IDS_REPLY_TIME_MS, pEchoReply->RoundTripTime);

                ConResPrintf(StdOut, IDS_REPLY_TTL, pEchoReply->Options.Ttl);

                if (pEchoReply->RoundTripTime < RTTMin || RTTMin == 0)
                    RTTMin = pEchoReply->RoundTripTime;

                if (pEchoReply->RoundTripTime > RTTMax || RTTMax == 0)
                    RTTMax = pEchoReply->RoundTripTime;

                RTTTotal += pEchoReply->RoundTripTime;
                break;
            }

            case IP_DEST_NET_UNREACHABLE:
                ConResPrintf(StdOut, IDS_DEST_NET_UNREACHABLE);
                break;

            case IP_DEST_HOST_UNREACHABLE:
                ConResPrintf(StdOut, IDS_DEST_HOST_UNREACHABLE);
                break;

            case IP_TTL_EXPIRED_TRANSIT:
                ConResPrintf(StdOut, IDS_TTL_EXPIRED);
                break;

            default:
                ConResPrintf(StdOut, IDS_REPLY_STATUS, pEchoReply->Status);
                break;
            }
        }
    }

    free(ReplyBuffer);
}