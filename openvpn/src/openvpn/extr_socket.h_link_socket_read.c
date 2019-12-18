#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct link_socket_actual {int /*<<< orphan*/  dest; } ;
struct TYPE_6__ {TYPE_2__* lsa; int /*<<< orphan*/  proto; } ;
struct link_socket {TYPE_3__ info; } ;
struct buffer {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dest; } ;
struct TYPE_5__ {TYPE_1__ actual; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr_copy_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int link_socket_read_tcp (struct link_socket*,struct buffer*) ; 
 int link_socket_read_udp_posix (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 int link_socket_read_udp_win32 (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 scalar_t__ proto_is_tcp (int /*<<< orphan*/ ) ; 
 scalar_t__ proto_is_udp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
link_socket_read(struct link_socket *sock,
                 struct buffer *buf,
                 struct link_socket_actual *from)
{
    if (proto_is_udp(sock->info.proto)) /* unified UDPv4 and UDPv6 */
    {
        int res;

#ifdef _WIN32
        res = link_socket_read_udp_win32(sock, buf, from);
#else
        res = link_socket_read_udp_posix(sock, buf, from);
#endif
        return res;
    }
    else if (proto_is_tcp(sock->info.proto)) /* unified TCPv4 and TCPv6 */
    {
        /* from address was returned by accept */
        addr_copy_sa(&from->dest, &sock->info.lsa->actual.dest);
        return link_socket_read_tcp(sock, buf);
    }
    else
    {
        ASSERT(0);
        return -1; /* NOTREACHED */
    }
}