#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_4__ {TYPE_1__ sa; } ;
struct openvpn_sockaddr {TYPE_2__ addr; } ;
struct link_socket_actual {struct openvpn_sockaddr dest; } ;
struct gc_arena {int dummy; } ;
struct addrinfo {int dummy; } ;
typedef  scalar_t__ socket_descriptor_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct link_socket_actual) ; 
 int D_LINK_ERRORS ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int M_ERR ; 
 int M_ERRNO ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ SOCKET_UNDEFINED ; 
 int /*<<< orphan*/  addrlist_match (struct openvpn_sockaddr*,struct addrinfo*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  get_signal (int volatile*) ; 
 int /*<<< orphan*/  management_sleep (int) ; 
 int /*<<< orphan*/  msg (int,char*,...) ; 
 scalar_t__ openvpn_close_socket (scalar_t__) ; 
 int /*<<< orphan*/  openvpn_fd_set (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openvpn_getaddrinfo (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct addrinfo**) ; 
 int /*<<< orphan*/  print_link_socket_actual (struct link_socket_actual*,struct gc_arena*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ socket_defined (scalar_t__) ; 
 scalar_t__ socket_do_accept (scalar_t__,struct link_socket_actual*,int) ; 
 int /*<<< orphan*/  socket_do_listen (scalar_t__,struct addrinfo const*,int,int) ; 
 int /*<<< orphan*/  tcp_connection_established (struct link_socket_actual*) ; 

__attribute__((used)) static socket_descriptor_t
socket_listen_accept(socket_descriptor_t sd,
                     struct link_socket_actual *act,
                     const char *remote_dynamic,
                     const struct addrinfo *local,
                     bool do_listen,
                     bool nowait,
                     volatile int *signal_received)
{
    struct gc_arena gc = gc_new();
    /* struct openvpn_sockaddr *remote = &act->dest; */
    struct openvpn_sockaddr remote_verify = act->dest;
    socket_descriptor_t new_sd = SOCKET_UNDEFINED;

    CLEAR(*act);
    socket_do_listen(sd, local, do_listen, true);

    while (true)
    {
        int status;
        fd_set reads;
        struct timeval tv;

        FD_ZERO(&reads);
        openvpn_fd_set(sd, &reads);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        status = select(sd + 1, &reads, NULL, NULL, &tv);

        get_signal(signal_received);
        if (*signal_received)
        {
            gc_free(&gc);
            return sd;
        }

        if (status < 0)
        {
            msg(D_LINK_ERRORS | M_ERRNO, "TCP: select() failed");
        }

        if (status <= 0)
        {
            management_sleep(1);
            continue;
        }

        new_sd = socket_do_accept(sd, act, nowait);

        if (socket_defined(new_sd))
        {
            struct addrinfo *ai = NULL;
            if (remote_dynamic)
            {
                openvpn_getaddrinfo(0, remote_dynamic, NULL, 1, NULL,
                                    remote_verify.addr.sa.sa_family, &ai);
            }

            if (ai && !addrlist_match(&remote_verify, ai))
            {
                msg(M_WARN,
                    "TCP NOTE: Rejected connection attempt from %s due to --remote setting",
                    print_link_socket_actual(act, &gc));
                if (openvpn_close_socket(new_sd))
                {
                    msg(M_ERR, "TCP: close socket failed (new_sd)");
                }
                freeaddrinfo(ai);
            }
            else
            {
                if (ai)
                {
                    freeaddrinfo(ai);
                }
                break;
            }
        }
        management_sleep(1);
    }

    if (!nowait && openvpn_close_socket(sd))
    {
        msg(M_ERR, "TCP: close socket failed (sd)");
    }

    tcp_connection_established(act);

    gc_free(&gc);
    return new_sd;
}