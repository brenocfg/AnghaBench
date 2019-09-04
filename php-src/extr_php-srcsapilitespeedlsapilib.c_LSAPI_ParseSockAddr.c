#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_un {char* sun_path; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {void* sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 void* INADDR_BROADCAST ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 void* inet_addr (char*) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int LSAPI_ParseSockAddr( const char * pBind, struct sockaddr * pAddr )
{
    char achAddr[256];
    char * p = achAddr;
    char * pEnd;
    struct addrinfo *res, hints;
    int  doAddrInfo = 0;
    int port;

    if ( !pBind )
        return -1;

    while( isspace( *pBind ) )
        ++pBind;

    strncpy( achAddr, pBind, 256 );

    switch( *p )
    {
    case '/':
        pAddr->sa_family = AF_UNIX;
        strncpy( ((struct sockaddr_un *)pAddr)->sun_path, p,
                sizeof(((struct sockaddr_un *)pAddr)->sun_path) );
        return 0;

    case '[':
        pAddr->sa_family = AF_INET6;
        ++p;
        pEnd = strchr( p, ']' );
        if ( !pEnd )
            return -1;
        *pEnd++ = 0;

        if ( *p == '*' )
        {
            strcpy( achAddr, "::" );
            p = achAddr;
        }
        doAddrInfo = 1;
        break;

    default:
        pAddr->sa_family = AF_INET;
        pEnd = strchr( p, ':' );
        if ( !pEnd )
            return -1;
        *pEnd++ = 0;

        doAddrInfo = 0;
        if ( *p == '*' )
        {
            ((struct sockaddr_in *)pAddr)->sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else if (!strcasecmp( p, "localhost" ) )
            ((struct sockaddr_in *)pAddr)->sin_addr.s_addr = htonl( INADDR_LOOPBACK );
        else
        {
            ((struct sockaddr_in *)pAddr)->sin_addr.s_addr = inet_addr( p );
            if ( ((struct sockaddr_in *)pAddr)->sin_addr.s_addr == INADDR_BROADCAST)
            {
                doAddrInfo = 1;
            }
        }
        break;
    }
    if ( *pEnd == ':' )
        ++pEnd;

    port = atoi( pEnd );
    if (( port <= 0 )||( port > 65535 ))
        return -1;
    if ( doAddrInfo )
    {

        memset(&hints, 0, sizeof(hints));

        hints.ai_family   = pAddr->sa_family;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        if ( getaddrinfo(p, NULL, &hints, &res) )
        {
            return -1;
        }

        memcpy(pAddr, res->ai_addr, res->ai_addrlen);
        freeaddrinfo(res);
    }

    if ( pAddr->sa_family == AF_INET )
        ((struct sockaddr_in *)pAddr)->sin_port = htons( port );
    else
        ((struct sockaddr_in6 *)pAddr)->sin6_port = htons( port );
    return 0;

}