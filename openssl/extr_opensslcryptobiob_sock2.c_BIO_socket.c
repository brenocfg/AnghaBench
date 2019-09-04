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

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_BIO_SOCKET ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_CREATE_SOCKET ; 
 int BIO_sock_init () ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  SYS_F_SOCKET ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 int socket (int,int,int) ; 

int BIO_socket(int domain, int socktype, int protocol, int options)
{
    int sock = -1;

    if (BIO_sock_init() != 1)
        return INVALID_SOCKET;

    sock = socket(domain, socktype, protocol);
    if (sock == -1) {
        SYSerr(SYS_F_SOCKET, get_last_socket_error());
        BIOerr(BIO_F_BIO_SOCKET, BIO_R_UNABLE_TO_CREATE_SOCKET);
        return INVALID_SOCKET;
    }

    return sock;
}