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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct socks_proxy_info {scalar_t__* authfile; } ;
typedef  int ssize_t ;
typedef  scalar_t__ socket_descriptor_t ;
typedef  int /*<<< orphan*/  method_sel ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int D_LINK_ERRORS ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int M_ERRNO ; 
 int /*<<< orphan*/  get_signal (int volatile*) ; 
 int /*<<< orphan*/  msg (int,char*) ; 
 int /*<<< orphan*/  openvpn_fd_set (scalar_t__,int /*<<< orphan*/ *) ; 
 int recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int send (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socks_username_password_auth (struct socks_proxy_info*,scalar_t__,int volatile*) ; 

__attribute__((used)) static bool
socks_handshake(struct socks_proxy_info *p,
                socket_descriptor_t sd,
                volatile int *signal_received)
{
    char buf[2];
    int len = 0;
    const int timeout_sec = 5;
    ssize_t size;

    /* VER = 5, NMETHODS = 1, METHODS = [0 (no auth)] */
    char method_sel[3] = { 0x05, 0x01, 0x00 };
    if (p->authfile[0])
    {
        method_sel[2] = 0x02; /* METHODS = [2 (plain login)] */

    }
    size = send(sd, method_sel, sizeof(method_sel), MSG_NOSIGNAL);
    if (size != sizeof(method_sel))
    {
        msg(D_LINK_ERRORS | M_ERRNO, "socks_handshake: TCP port write failed on send()");
        return false;
    }

    while (len < 2)
    {
        int status;
        ssize_t size;
        fd_set reads;
        struct timeval tv;
        char c;

        FD_ZERO(&reads);
        openvpn_fd_set(sd, &reads);
        tv.tv_sec = timeout_sec;
        tv.tv_usec = 0;

        status = select(sd + 1, &reads, NULL, NULL, &tv);

        get_signal(signal_received);
        if (*signal_received)
        {
            return false;
        }

        /* timeout? */
        if (status == 0)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "socks_handshake: TCP port read timeout expired");
            return false;
        }

        /* error */
        if (status < 0)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "socks_handshake: TCP port read failed on select()");
            return false;
        }

        /* read single char */
        size = recv(sd, &c, 1, MSG_NOSIGNAL);

        /* error? */
        if (size != 1)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "socks_handshake: TCP port read failed on recv()");
            return false;
        }

        /* store char in buffer */
        buf[len++] = c;
    }

    /* VER == 5 */
    if (buf[0] != '\x05')
    {
        msg(D_LINK_ERRORS, "socks_handshake: Socks proxy returned bad status");
        return false;
    }

    /* validate that the auth method returned is the one sent */
    if (buf[1] != method_sel[2])
    {
        msg(D_LINK_ERRORS, "socks_handshake: Socks proxy returned unexpected auth");
        return false;
    }

    /* select the appropriate authentication method */
    switch (buf[1])
    {
        case 0: /* no authentication */
            break;

        case 2: /* login/password */
            if (!p->authfile[0])
            {
                msg(D_LINK_ERRORS, "socks_handshake: server asked for username/login auth but we were "
                    "not provided any credentials");
                return false;
            }

            if (!socks_username_password_auth(p, sd, signal_received))
            {
                return false;
            }

            break;

        default: /* unknown auth method */
            msg(D_LINK_ERRORS, "socks_handshake: unknown SOCKS auth method");
            return false;
    }

    return true;
}