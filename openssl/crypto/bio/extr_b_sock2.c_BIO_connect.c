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
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_sockaddr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_ADDR_sockaddr_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BIO_F_BIO_CONNECT ; 
 int /*<<< orphan*/  BIO_R_CONNECT_ERROR ; 
 int /*<<< orphan*/  BIO_R_INVALID_SOCKET ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_KEEPALIVE ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_NODELAY ; 
 int BIO_SOCK_KEEPALIVE ; 
 int BIO_SOCK_NODELAY ; 
 int BIO_SOCK_NONBLOCK ; 
 int /*<<< orphan*/  BIO_sock_should_retry (int) ; 
 int /*<<< orphan*/  BIO_socket_nbio (int,int) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LIB_SYS ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

int BIO_connect(int sock, const BIO_ADDR *addr, int options)
{
    const int on = 1;

    if (sock == -1) {
        BIOerr(BIO_F_BIO_CONNECT, BIO_R_INVALID_SOCKET);
        return 0;
    }

    if (!BIO_socket_nbio(sock, (options & BIO_SOCK_NONBLOCK) != 0))
        return 0;

    if (options & BIO_SOCK_KEEPALIVE) {
        if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
                       (const void *)&on, sizeof(on)) != 0) {
            ERR_raise_data(ERR_LIB_SYS, get_last_socket_error(),
                           "calling setsockopt()");
            BIOerr(BIO_F_BIO_CONNECT, BIO_R_UNABLE_TO_KEEPALIVE);
            return 0;
        }
    }

    if (options & BIO_SOCK_NODELAY) {
        if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
                       (const void *)&on, sizeof(on)) != 0) {
            ERR_raise_data(ERR_LIB_SYS, get_last_socket_error(),
                           "calling setsockopt()");
            BIOerr(BIO_F_BIO_CONNECT, BIO_R_UNABLE_TO_NODELAY);
            return 0;
        }
    }

    if (connect(sock, BIO_ADDR_sockaddr(addr),
                BIO_ADDR_sockaddr_size(addr)) == -1) {
        if (!BIO_sock_should_retry(-1)) {
            ERR_raise_data(ERR_LIB_SYS, get_last_socket_error(),
                           "calling connect()");
            BIOerr(BIO_F_BIO_CONNECT, BIO_R_CONNECT_ERROR);
        }
        return 0;
    }
    return 1;
}