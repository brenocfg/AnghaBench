#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_12__ {TYPE_8__ sa; } ;
struct openvpn_sockaddr {TYPE_4__ addr; } ;
struct TYPE_14__ {scalar_t__ proto; TYPE_5__* lsa; int /*<<< orphan*/  af; } ;
struct link_socket {scalar_t__ inetd; TYPE_6__ info; scalar_t__ sd; } ;
struct frame {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  local_addr ;
struct TYPE_9__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_10__ {TYPE_1__ sa; } ;
struct TYPE_11__ {TYPE_2__ addr; } ;
struct TYPE_15__ {TYPE_3__ dest; } ;
struct TYPE_13__ {int /*<<< orphan*/  bind_local; TYPE_7__ actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  D_SOCKET_DEBUG ; 
 scalar_t__ INETD_NOWAIT ; 
 int /*<<< orphan*/  M_WARN ; 
 scalar_t__ PROTO_TCP_SERVER ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ getsockname (scalar_t__,TYPE_8__*,int*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  proto2ascii (scalar_t__,int,...) ; 
 scalar_t__ socket_listen_accept (scalar_t__,TYPE_7__*,char const*,int /*<<< orphan*/ ,int,int,int volatile*) ; 

__attribute__((used)) static
void
phase2_inetd(struct link_socket *sock, const struct frame *frame,
             const char *remote_dynamic, volatile int *signal_received)
{
    bool remote_changed = false;

    if (sock->info.proto == PROTO_TCP_SERVER)
    {
        /* AF_INET as default (and fallback) for inetd */
        sock->info.lsa->actual.dest.addr.sa.sa_family = AF_INET;
#ifdef HAVE_GETSOCKNAME
        {
            /* inetd: hint family type for dest = local's */
            struct openvpn_sockaddr local_addr;
            socklen_t addrlen = sizeof(local_addr);
            if (getsockname(sock->sd, &local_addr.addr.sa, &addrlen) == 0)
            {
                sock->info.lsa->actual.dest.addr.sa.sa_family = local_addr.addr.sa.sa_family;
                dmsg(D_SOCKET_DEBUG, "inetd(%s): using sa_family=%d from getsockname(%d)",
                     proto2ascii(sock->info.proto, sock->info.af, false),
                     local_addr.addr.sa.sa_family, (int)sock->sd);
            }
            else
            {
                msg(M_WARN, "inetd(%s): getsockname(%d) failed, using AF_INET",
                    proto2ascii(sock->info.proto, sock->info.af, false), (int)sock->sd);
            }
        }
#else  /* ifdef HAVE_GETSOCKNAME */
        msg(M_WARN, "inetd(%s): this OS does not provide the getsockname() "
            "function, using AF_INET",
            proto2ascii(sock->info.proto, false));
#endif /* ifdef HAVE_GETSOCKNAME */
        sock->sd =
            socket_listen_accept(sock->sd,
                                 &sock->info.lsa->actual,
                                 remote_dynamic,
                                 sock->info.lsa->bind_local,
                                 false,
                                 sock->inetd == INETD_NOWAIT,
                                 signal_received);

    }
    ASSERT(!remote_changed);
}