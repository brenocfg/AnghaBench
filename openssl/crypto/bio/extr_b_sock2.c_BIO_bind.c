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
 int /*<<< orphan*/  BIO_F_BIO_BIND ; 
 int /*<<< orphan*/  BIO_R_INVALID_SOCKET ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_BIND_SOCKET ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_REUSEADDR ; 
 int BIO_SOCK_REUSEADDR ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_LIB_SYS ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

int BIO_bind(int sock, const BIO_ADDR *addr, int options)
{
# ifndef OPENSSL_SYS_WINDOWS
    int on = 1;
# endif

    if (sock == -1) {
        BIOerr(BIO_F_BIO_BIND, BIO_R_INVALID_SOCKET);
        return 0;
    }

# ifndef OPENSSL_SYS_WINDOWS
    /*
     * SO_REUSEADDR has different behavior on Windows than on
     * other operating systems, don't set it there.
     */
    if (options & BIO_SOCK_REUSEADDR) {
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                       (const void *)&on, sizeof(on)) != 0) {
            ERR_raise_data(ERR_LIB_SYS, get_last_socket_error(),
                           "calling setsockopt()");
            BIOerr(BIO_F_BIO_BIND, BIO_R_UNABLE_TO_REUSEADDR);
            return 0;
        }
    }
# endif

    if (bind(sock, BIO_ADDR_sockaddr(addr), BIO_ADDR_sockaddr_size(addr)) != 0) {
        ERR_raise_data(ERR_LIB_SYS, get_last_socket_error(),
                       "calling bind()");
        BIOerr(BIO_F_BIO_BIND, BIO_R_UNABLE_TO_BIND_SOCKET);
        return 0;
    }

    return 1;
}