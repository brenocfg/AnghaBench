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
struct TYPE_4__ {TYPE_1__* lsa; int /*<<< orphan*/  af; int /*<<< orphan*/  proto; } ;
struct link_socket {int resolve_retry_seconds; TYPE_2__ info; int /*<<< orphan*/  remote_port; scalar_t__ remote_host; int /*<<< orphan*/  dns_cache; int /*<<< orphan*/  sockflags; } ;
struct gc_arena {int dummy; } ;
struct addrinfo {int dummy; } ;
struct TYPE_3__ {struct addrinfo* current_remote; int /*<<< orphan*/  actual; struct addrinfo* remote_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_SOCKET_DEBUG ; 
 unsigned int GETADDR_DATAGRAM ; 
 unsigned int GETADDR_FATAL ; 
 unsigned int GETADDR_MENTION_RESOLVE_RETRY ; 
 int GETADDR_RESOLVE ; 
 unsigned int GETADDR_TRY_ONCE ; 
 int GETADDR_UPDATE_MANAGEMENT_STATE ; 
 int /*<<< orphan*/  M_INFO ; 
 int RESOLV_RETRY_INFINITE ; 
 int SIGUSR1 ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,unsigned int,int,int,int volatile,int) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int get_cached_dns_entry (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct addrinfo**) ; 
 scalar_t__ link_socket_actual_defined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int openvpn_getaddrinfo (unsigned int,scalar_t__,int /*<<< orphan*/ ,int,int volatile*,int /*<<< orphan*/ ,struct addrinfo**) ; 
 int /*<<< orphan*/  print_link_socket_actual (int /*<<< orphan*/ *,struct gc_arena*) ; 
 scalar_t__ proto_is_dgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_actual_address (int /*<<< orphan*/ *,struct addrinfo*) ; 
 unsigned int sf2gaf (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resolve_remote(struct link_socket *sock,
               int phase,
               const char **remote_dynamic,
               volatile int *signal_received)
{
    struct gc_arena gc = gc_new();

    /* resolve remote address if undefined */
    if (!sock->info.lsa->remote_list)
    {
        if (sock->remote_host)
        {
            unsigned int flags = sf2gaf(GETADDR_RESOLVE|GETADDR_UPDATE_MANAGEMENT_STATE, sock->sockflags);
            int retry = 0;
            int status = -1;
            struct addrinfo *ai;
            if (proto_is_dgram(sock->info.proto))
            {
                flags |= GETADDR_DATAGRAM;
            }

            if (sock->resolve_retry_seconds == RESOLV_RETRY_INFINITE)
            {
                if (phase == 2)
                {
                    flags |= (GETADDR_TRY_ONCE | GETADDR_FATAL);
                }
                retry = 0;
            }
            else if (phase == 1)
            {
                if (sock->resolve_retry_seconds)
                {
                    retry = 0;
                }
                else
                {
                    flags |= (GETADDR_FATAL | GETADDR_MENTION_RESOLVE_RETRY);
                    retry = 0;
                }
            }
            else if (phase == 2)
            {
                if (sock->resolve_retry_seconds)
                {
                    flags |= GETADDR_FATAL;
                    retry = sock->resolve_retry_seconds;
                }
                else
                {
                    ASSERT(0);
                }
            }
            else
            {
                ASSERT(0);
            }


            status = get_cached_dns_entry(sock->dns_cache,
                                          sock->remote_host,
                                          sock->remote_port,
                                          sock->info.af,
                                          flags, &ai);
            if (status)
            {
                status = openvpn_getaddrinfo(flags, sock->remote_host, sock->remote_port,
                                             retry, signal_received, sock->info.af, &ai);
            }

            if (status == 0)
            {
                sock->info.lsa->remote_list = ai;
                sock->info.lsa->current_remote = ai;

                dmsg(D_SOCKET_DEBUG, "RESOLVE_REMOTE flags=0x%04x phase=%d rrs=%d sig=%d status=%d",
                     flags,
                     phase,
                     retry,
                     signal_received ? *signal_received : -1,
                     status);
            }
            if (signal_received)
            {
                if (*signal_received)
                {
                    goto done;
                }
            }
            if (status!=0)
            {
                if (signal_received)
                {
                    *signal_received = SIGUSR1;
                }
                goto done;
            }
        }
    }

    /* should we re-use previous active remote address? */
    if (link_socket_actual_defined(&sock->info.lsa->actual))
    {
        msg(M_INFO, "TCP/UDP: Preserving recently used remote address: %s",
            print_link_socket_actual(&sock->info.lsa->actual, &gc));
        if (remote_dynamic)
        {
            *remote_dynamic = NULL;
        }
    }
    else
    {
        CLEAR(sock->info.lsa->actual);
        if (sock->info.lsa->current_remote)
        {
            set_actual_address(&sock->info.lsa->actual,
                               sock->info.lsa->current_remote);
        }
    }

done:
    gc_free(&gc);
}