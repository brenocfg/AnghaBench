#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ af; scalar_t__ proto; TYPE_4__* lsa; } ;
struct signal_info {int signal_received; char* remote_host; int sd; TYPE_5__ info; scalar_t__ socks_proxy; scalar_t__ bind_local; scalar_t__ inetd; scalar_t__ resolve_retry_seconds; } ;
struct link_socket {int signal_received; char* remote_host; int sd; TYPE_5__ info; scalar_t__ socks_proxy; scalar_t__ bind_local; scalar_t__ inetd; scalar_t__ resolve_retry_seconds; } ;
struct frame {int dummy; } ;
struct TYPE_12__ {scalar_t__ ai_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  sa; } ;
struct TYPE_8__ {TYPE_1__ addr; } ;
struct TYPE_9__ {TYPE_2__ dest; } ;
struct TYPE_10__ {TYPE_3__ actual; TYPE_6__* bind_local; TYPE_6__* current_remote; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  ASSERT (struct signal_info*) ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ PROTO_TCP_CLIENT ; 
 scalar_t__ PROTO_TCP_SERVER ; 
 scalar_t__ PROTO_UDP ; 
 int SIGUSR1 ; 
 int SOCKET_UNDEFINED ; 
 int /*<<< orphan*/  addr_family_name (scalar_t__) ; 
 int /*<<< orphan*/  create_socket (struct signal_info*,TYPE_6__*) ; 
 int /*<<< orphan*/  linksock_print_addr (struct signal_info*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  phase2_inetd (struct signal_info*,struct frame const*,char const*,int*) ; 
 int /*<<< orphan*/  phase2_set_socket_flags (struct signal_info*) ; 
 int /*<<< orphan*/  phase2_socks_client (struct signal_info*,struct signal_info*) ; 
 int /*<<< orphan*/  phase2_tcp_client (struct signal_info*,struct signal_info*) ; 
 int /*<<< orphan*/  phase2_tcp_server (struct signal_info*,char const*,int*) ; 
 int /*<<< orphan*/  protect_fd_nonlocal (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_remote (struct signal_info*,int,char const**,int*) ; 
 int /*<<< orphan*/  socket_frame_init (struct frame const*,struct signal_info*) ; 

void
link_socket_init_phase2(struct link_socket *sock,
                        const struct frame *frame,
                        struct signal_info *sig_info)
{
    const char *remote_dynamic = NULL;
    int sig_save = 0;

    ASSERT(sock);
    ASSERT(sig_info);

    if (sig_info->signal_received)
    {
        sig_save = sig_info->signal_received;
        sig_info->signal_received = 0;
    }

    /* initialize buffers */
    socket_frame_init(frame, sock);

    /*
     * Pass a remote name to connect/accept so that
     * they can test for dynamic IP address changes
     * and throw a SIGUSR1 if appropriate.
     */
    if (sock->resolve_retry_seconds)
    {
        remote_dynamic = sock->remote_host;
    }

    /* were we started by inetd or xinetd? */
    if (sock->inetd)
    {
        phase2_inetd(sock, frame, remote_dynamic,  &sig_info->signal_received);
        if (sig_info->signal_received)
        {
            goto done;
        }

    }
    else
    {
        /* Second chance to resolv/create socket */
        resolve_remote(sock, 2, &remote_dynamic,  &sig_info->signal_received);

        /* If a valid remote has been found, create the socket with its addrinfo */
        if (sock->info.lsa->current_remote)
        {
            create_socket(sock, sock->info.lsa->current_remote);
        }

        /* If socket has not already been created create it now */
        if (sock->sd == SOCKET_UNDEFINED)
        {
            /* If we have no --remote and have still not figured out the
             * protocol family to use we will use the first of the bind */

            if (sock->bind_local  && !sock->remote_host && sock->info.lsa->bind_local)
            {
                /* Warn if this is because neither v4 or v6 was specified
                 * and we should not connect a remote */
                if (sock->info.af == AF_UNSPEC)
                {
                    msg(M_WARN, "Could not determine IPv4/IPv6 protocol. Using %s",
                        addr_family_name(sock->info.lsa->bind_local->ai_family));
                    sock->info.af = sock->info.lsa->bind_local->ai_family;
                }

                create_socket(sock, sock->info.lsa->bind_local);
            }
        }

        /* Socket still undefined, give a warning and abort connection */
        if (sock->sd == SOCKET_UNDEFINED)
        {
            msg(M_WARN, "Could not determine IPv4/IPv6 protocol");
            sig_info->signal_received = SIGUSR1;
            goto done;
        }

        if (sig_info->signal_received)
        {
            goto done;
        }

        if (sock->info.proto == PROTO_TCP_SERVER)
        {
            phase2_tcp_server(sock, remote_dynamic,
                              &sig_info->signal_received);
        }
        else if (sock->info.proto == PROTO_TCP_CLIENT)
        {
            phase2_tcp_client(sock, sig_info);

        }
        else if (sock->info.proto == PROTO_UDP && sock->socks_proxy)
        {
            phase2_socks_client(sock, sig_info);
        }
#ifdef TARGET_ANDROID
        if (sock->sd != -1)
        {
            protect_fd_nonlocal(sock->sd, &sock->info.lsa->actual.dest.addr.sa);
        }
#endif
        if (sig_info->signal_received)
        {
            goto done;
        }
    }

    phase2_set_socket_flags(sock);
    linksock_print_addr(sock);

done:
    if (sig_save)
    {
        if (!sig_info->signal_received)
        {
            sig_info->signal_received = sig_save;
        }
    }
}