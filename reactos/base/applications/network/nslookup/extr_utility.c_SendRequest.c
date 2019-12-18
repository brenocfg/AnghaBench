#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {scalar_t__ debug; int /*<<< orphan*/  port; int /*<<< orphan*/  DefaultServerAddress; scalar_t__ d2; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_1__ sin_addr; void* sin_port; void* sin_family; } ;
typedef  int /*<<< orphan*/  SendAddr ;
typedef  scalar_t__ SOCKET ;
typedef  TYPE_2__ SOCKADDR_IN ;
typedef  int /*<<< orphan*/  SOCKADDR ;
typedef  int /*<<< orphan*/  RecAddr2 ;
typedef  int /*<<< orphan*/  RecAddr ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/ * PSHORT ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PrintD2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintDebug (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 TYPE_3__ State ; 
 scalar_t__ TRUE ; 
#define  WSAEACCES 150 
#define  WSAEADDRNOTAVAIL 149 
#define  WSAEAFNOSUPPORT 148 
#define  WSAECONNABORTED 147 
#define  WSAECONNRESET 146 
#define  WSAEDESTADDRREQ 145 
#define  WSAEFAULT 144 
#define  WSAEHOSTUNREACH 143 
#define  WSAEINPROGRESS 142 
#define  WSAEINTR 141 
#define  WSAEINVAL 140 
#define  WSAEMSGSIZE 139 
#define  WSAENETDOWN 138 
#define  WSAENETRESET 137 
#define  WSAENETUNREACH 136 
#define  WSAENOBUFS 135 
#define  WSAENOTCONN 134 
#define  WSAENOTSOCK 133 
#define  WSAEOPNOTSUPP 132 
#define  WSAESHUTDOWN 131 
#define  WSAETIMEDOUT 130 
#define  WSAEWOULDBLOCK 129 
 int WSAGetLastError () ; 
#define  WSANOTINITIALISED 128 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int recvfrom (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int sendto (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL SendRequest( PCHAR pInBuffer,
                  ULONG InBufferLength,
                  PCHAR pOutBuffer,
                  PULONG pOutBufferLength )
{
    int j;
    USHORT RequestID, ResponseID;
    BOOL bWait;
    SOCKET s;
    SOCKADDR_IN RecAddr, RecAddr2, SendAddr;
    int SendAddrLen = sizeof(SendAddr);

    RtlZeroMemory( &RecAddr, sizeof(SOCKADDR_IN) );
    RtlZeroMemory( &RecAddr2, sizeof(SOCKADDR_IN) );
    RtlZeroMemory( &SendAddr, sizeof(SOCKADDR_IN) );

    /* Pull the request ID from the buffer. */
    RequestID = ntohs( ((PSHORT)&pInBuffer[0])[0] );

    /* If D2 flags is enabled, then display D2 information. */
    if( State.d2 ) PrintD2( pInBuffer, InBufferLength );

    /* Create the sockets for both send and receive. */
    s = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

    if (s == INVALID_SOCKET)
        return FALSE;

    /* Set up the structure to tell it where we are going. */
    RecAddr.sin_family = AF_INET;
    RecAddr.sin_port = htons( State.port );
    RecAddr.sin_addr.s_addr = inet_addr( State.DefaultServerAddress );

    /* Set up the structure to tell it what port to listen on. */
    RecAddr2.sin_family = AF_INET;
    RecAddr2.sin_port = htons( State.port );
    RecAddr2.sin_addr.s_addr = htonl( INADDR_ANY );

    /* Bind the receive socket. */
    bind( s, (SOCKADDR*)&RecAddr2, sizeof(RecAddr2) );

    /* Send the datagram to the DNS server. */
    j = sendto( s,
                pInBuffer,
                InBufferLength,
                0,
                (SOCKADDR*)&RecAddr,
                sizeof(RecAddr) );
    if( j == SOCKET_ERROR )
    {
        switch( WSAGetLastError() )
        {
        case WSANOTINITIALISED:
            _tprintf( _T("sendto() failed with WSANOTINITIALIZED\n") );
            break;
        case WSAENETDOWN:
            _tprintf( _T("sendto() failed with WSAENETDOWN\n") );
            break;
        case WSAEACCES:
            _tprintf( _T("sendto() failed with WSAEACCES\n") );
            break;
        case WSAEINVAL:
            _tprintf( _T("sendto() failed with WSAEINVAL\n") );
            break;
        case WSAEINTR:
            _tprintf( _T("sendto() failed with WSAEINTR\n") );
            break;
        case WSAEINPROGRESS:
            _tprintf( _T("sendto() failed with WSAEINPROGRESS\n") );
            break;
        case WSAEFAULT:
            _tprintf( _T("sendto() failed with WSAEFAULT\n") );
            break;
        case WSAENETRESET:
            _tprintf( _T("sendto() failed with WSAENETRESET\n") );
            break;
        case WSAENOBUFS:
            _tprintf( _T("sendto() failed with WSAENOBUFS\n") );
            break;
        case WSAENOTCONN:
            _tprintf( _T("sendto() failed with WSAENOTCONN\n") );
            break;
        case WSAENOTSOCK:
            _tprintf( _T("sendto() failed with WSAENOTSOCK\n") );
            break;
        case WSAEOPNOTSUPP:
            _tprintf( _T("sendto() failed with WSAEOPNOTSUPP\n") );
            break;
        case WSAESHUTDOWN:
            _tprintf( _T("sendto() failed with WSAESHUTDOWN\n") );
            break;
        case WSAEWOULDBLOCK:
            _tprintf( _T("sendto() failed with WSAEWOULDBLOCK\n") );
            break;
        case WSAEMSGSIZE:
            _tprintf( _T("sendto() failed with WSAEMSGSIZE\n") );
            break;
        case WSAEHOSTUNREACH:
            _tprintf( _T("sendto() failed with WSAEHOSTUNREACH\n") );
            break;
        case WSAECONNABORTED:
            _tprintf( _T("sendto() failed with WSAECONNABORTED\n") );
            break;
        case WSAECONNRESET:
            _tprintf( _T("sendto() failed with WSAECONNRESET\n") );
            break;
        case WSAEADDRNOTAVAIL:
            _tprintf( _T("sendto() failed with WSAEADDRNOTAVAIL\n") );
            break;
        case WSAEAFNOSUPPORT:
            _tprintf( _T("sendto() failed with WSAEAFNOSUPPORT\n") );
            break;
        case WSAEDESTADDRREQ:
            _tprintf( _T("sendto() failed with WSAEDESTADDRREQ\n") );
            break;
        case WSAENETUNREACH:
            _tprintf( _T("sendto() failed with WSAENETUNREACH\n") );
            break;
        case WSAETIMEDOUT:
            _tprintf( _T("sendto() failed with WSAETIMEDOUT\n") );
            break;
        default:
            _tprintf( _T("sendto() failed with unknown error\n") );
        }

        closesocket( s );
        return FALSE;
    }

    bWait = TRUE;

    while( bWait )
    {
        /* Wait for the DNS reply. */
        j = recvfrom( s,
                      pOutBuffer,
                      *pOutBufferLength,
                      0,
                      (SOCKADDR*)&SendAddr,
                      &SendAddrLen );
        if( j == SOCKET_ERROR )
        {
            switch( WSAGetLastError() )
            {
            case WSANOTINITIALISED:
                _tprintf( _T("recvfrom() failed with WSANOTINITIALIZED\n") );
                break;
            case WSAENETDOWN:
                _tprintf( _T("recvfrom() failed with WSAENETDOWN\n") );
                break;
            case WSAEACCES:
                _tprintf( _T("recvfrom() failed with WSAEACCES\n") );
                break;
            case WSAEINVAL:
                _tprintf( _T("recvfrom() failed with WSAEINVAL\n") );
                break;
            case WSAEINTR:
                _tprintf( _T("recvfrom() failed with WSAEINTR\n") );
                break;
            case WSAEINPROGRESS:
                _tprintf( _T("recvfrom() failed with WSAEINPROGRESS\n") );
                break;
            case WSAEFAULT:
                _tprintf( _T("recvfrom() failed with WSAEFAULT\n") );
                break;
            case WSAENETRESET:
                _tprintf( _T("recvfrom() failed with WSAENETRESET\n") );
                break;
            case WSAENOBUFS:
                _tprintf( _T("recvfrom() failed with WSAENOBUFS\n") );
                break;
            case WSAENOTCONN:
                _tprintf( _T("recvfrom() failed with WSAENOTCONN\n") );
                break;
            case WSAENOTSOCK:
                _tprintf( _T("recvfrom() failed with WSAENOTSOCK\n") );
                break;
            case WSAEOPNOTSUPP:
                _tprintf( _T("recvfrom() failed with WSAEOPNOTSUPP\n") );
                break;
            case WSAESHUTDOWN:
                _tprintf( _T("recvfrom() failed with WSAESHUTDOWN\n") );
                break;
            case WSAEWOULDBLOCK:
                _tprintf( _T("recvfrom() failed with WSAEWOULDBLOCK\n") );
                break;
            case WSAEMSGSIZE:
                _tprintf( _T("recvfrom() failed with WSAEMSGSIZE\n") );
                break;
            case WSAEHOSTUNREACH:
                _tprintf( _T("recvfrom() failed with WSAEHOSTUNREACH\n") );
                break;
            case WSAECONNABORTED:
                _tprintf( _T("recvfrom() failed with WSAECONNABORTED\n") );
                break;
            case WSAECONNRESET:
                _tprintf( _T("recvfrom() failed with WSAECONNRESET\n") );
                break;
            case WSAEADDRNOTAVAIL:
                _tprintf( _T("recvfrom() failed with WSAEADDRNOTAVAIL\n") );
                break;
            case WSAEAFNOSUPPORT:
                _tprintf( _T("recvfrom() failed with WSAEAFNOSUPPORT\n") );
                break;
            case WSAEDESTADDRREQ:
                _tprintf( _T("recvfrom() failed with WSAEDESTADDRREQ\n") );
                break;
            case WSAENETUNREACH:
                _tprintf( _T("recvfrom() failed with WSAENETUNREACH\n") );
                break;
            case WSAETIMEDOUT:
                _tprintf( _T("recvfrom() failed with WSAETIMEDOUT\n") );
                break;
            default:
                _tprintf( _T("recvfrom() failed with unknown error\n") );
            }

            closesocket( s );
            return FALSE;
        }

        ResponseID = ntohs( ((PSHORT)&pOutBuffer[0])[0] );

        if( ResponseID == RequestID ) bWait = FALSE;
    }

    /* We don't need the sockets anymore. */
    closesocket( s );

    /* If debug information then display debug information. */
    if( State.debug ) PrintDebug( pOutBuffer, j );

    /* Return the real output buffer length. */
    *pOutBufferLength = j;

    return TRUE;
}