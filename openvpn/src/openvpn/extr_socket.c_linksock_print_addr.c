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
struct TYPE_11__ {TYPE_4__* lsa; int /*<<< orphan*/  af; int /*<<< orphan*/  proto; } ;
struct link_socket {scalar_t__ mode; TYPE_5__ info; scalar_t__ bind_local; scalar_t__ inetd; } ;
struct gc_arena {int dummy; } ;
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_7__ {scalar_t__ sa_family; } ;
struct TYPE_8__ {TYPE_1__ sa; } ;
struct TYPE_9__ {TYPE_2__ addr; } ;
struct TYPE_12__ {TYPE_3__ dest; } ;
struct TYPE_10__ {TYPE_6__ actual; struct addrinfo* bind_local; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct addrinfo*) ; 
 int D_INIT_MEDIUM ; 
 scalar_t__ LS_MODE_TCP_ACCEPT_FROM ; 
 int M_INFO ; 
 int /*<<< orphan*/  PS_SHOW_PORT_IF_DEFINED ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int const,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  print_link_socket_actual_ex (TYPE_6__*,char*,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  print_sockaddr (int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  proto2ascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
linksock_print_addr(struct link_socket *sock)
{
    struct gc_arena gc = gc_new();
    const int msglevel = (sock->mode == LS_MODE_TCP_ACCEPT_FROM) ? D_INIT_MEDIUM : M_INFO;

    /* print local address */
    if (sock->inetd)
    {
        msg(msglevel, "%s link local: [inetd]", proto2ascii(sock->info.proto, sock->info.af, true));
    }
    else if (sock->bind_local)
    {
        sa_family_t ai_family = sock->info.lsa->actual.dest.addr.sa.sa_family;
        /* Socket is always bound on the first matching address,
         * For bound sockets with no remote addr this is the element of
         * the list */
        struct addrinfo *cur;
        for (cur = sock->info.lsa->bind_local; cur; cur = cur->ai_next)
        {
            if (!ai_family || ai_family == cur->ai_family)
            {
                break;
            }
        }
        ASSERT(cur);
        msg(msglevel, "%s link local (bound): %s",
            proto2ascii(sock->info.proto, sock->info.af, true),
            print_sockaddr(cur->ai_addr,&gc));
    }
    else
    {
        msg(msglevel, "%s link local: (not bound)",
            proto2ascii(sock->info.proto, sock->info.af, true));
    }

    /* print active remote address */
    msg(msglevel, "%s link remote: %s",
        proto2ascii(sock->info.proto, sock->info.af, true),
        print_link_socket_actual_ex(&sock->info.lsa->actual,
                                    ":",
                                    PS_SHOW_PORT_IF_DEFINED,
                                    &gc));
    gc_free(&gc);
}