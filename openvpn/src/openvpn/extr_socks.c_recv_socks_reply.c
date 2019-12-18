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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_3__ sin_port; TYPE_3__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {TYPE_1__ in4; } ;
struct openvpn_sockaddr {TYPE_2__ addr; } ;
struct gc_arena {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ socket_descriptor_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int D_LINK_ERRORS ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int M_ERRNO ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  get_signal (int volatile*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_3__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 int /*<<< orphan*/  openvpn_fd_set (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_openvpn_sockaddr (struct openvpn_sockaddr*,struct gc_arena*) ; 
 int recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static bool
recv_socks_reply(socket_descriptor_t sd,
                 struct openvpn_sockaddr *addr,
                 volatile int *signal_received)
{
    char atyp = '\0';
    int alen = 0;
    int len = 0;
    char buf[22];
    const int timeout_sec = 5;

    if (addr != NULL)
    {
        addr->addr.in4.sin_family = AF_INET;
        addr->addr.in4.sin_addr.s_addr = htonl(INADDR_ANY);
        addr->addr.in4.sin_port = htons(0);
    }

    while (len < 4 + alen + 2)
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
            msg(D_LINK_ERRORS | M_ERRNO, "recv_socks_reply: TCP port read timeout expired");
            return false;
        }

        /* error */
        if (status < 0)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "recv_socks_reply: TCP port read failed on select()");
            return false;
        }

        /* read single char */
        size = recv(sd, &c, 1, MSG_NOSIGNAL);

        /* error? */
        if (size != 1)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "recv_socks_reply: TCP port read failed on recv()");
            return false;
        }

        if (len == 3)
        {
            atyp = c;
        }

        if (len == 4)
        {
            switch (atyp)
            {
                case '\x01':    /* IP V4 */
                    alen = 4;
                    break;

                case '\x03':    /* DOMAINNAME */
                    alen = (unsigned char) c;
                    break;

                case '\x04':    /* IP V6 */
                    alen = 16;
                    break;

                default:
                    msg(D_LINK_ERRORS, "recv_socks_reply: Socks proxy returned bad address type");
                    return false;
            }
        }

        /* store char in buffer */
        if (len < (int)sizeof(buf))
        {
            buf[len] = c;
        }
        ++len;
    }

    /* VER == 5 && REP == 0 (succeeded) */
    if (buf[0] != '\x05' || buf[1] != '\x00')
    {
        msg(D_LINK_ERRORS, "recv_socks_reply: Socks proxy returned bad reply");
        return false;
    }

    /* ATYP == 1 (IP V4 address) */
    if (atyp == '\x01' && addr != NULL)
    {
        memcpy(&addr->addr.in4.sin_addr, buf + 4, sizeof(addr->addr.in4.sin_addr));
        memcpy(&addr->addr.in4.sin_port, buf + 8, sizeof(addr->addr.in4.sin_port));
        struct gc_arena gc = gc_new();
        msg(M_INFO, "SOCKS proxy wants us to send UDP to %s",
            print_openvpn_sockaddr(addr, &gc));
        gc_free(&gc);
    }


    return true;
}