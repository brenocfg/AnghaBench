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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  flag ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int listen (int,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int LSAPI_CreateListenSock2( const struct sockaddr * pServerAddr, int backlog )
{
    int ret;
    int fd;
    int flag = 1;
    int addr_len;

    switch( pServerAddr->sa_family )
    {
    case AF_INET:
        addr_len = 16;
        break;
    case AF_INET6:
        addr_len = sizeof( struct sockaddr_in6 );
        break;
    case AF_UNIX:
        addr_len = sizeof( struct sockaddr_un );
        unlink( ((struct sockaddr_un *)pServerAddr)->sun_path );
        break;
    default:
        return -1;
    }

    fd = socket( pServerAddr->sa_family, SOCK_STREAM, 0 );
    if ( fd == -1 )
        return -1;

    fcntl( fd, F_SETFD, FD_CLOEXEC );

    if(setsockopt( fd, SOL_SOCKET, SO_REUSEADDR,
                (char *)( &flag ), sizeof(flag)) == 0)
    {
        ret = bind( fd, pServerAddr, addr_len );
        if ( !ret )
        {
            ret = listen( fd, backlog );
            if ( !ret )
                return fd;
        }
    }

    ret = errno;
    close(fd);
    errno = ret;
    return -1;
}