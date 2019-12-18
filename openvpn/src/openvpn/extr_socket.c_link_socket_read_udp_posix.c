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
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
struct TYPE_6__ {TYPE_2__ addr; } ;
struct link_socket_actual {TYPE_3__ dest; } ;
struct TYPE_4__ {scalar_t__ proto; int /*<<< orphan*/  af; } ;
struct link_socket {int sockflags; int /*<<< orphan*/  sd; TYPE_1__ info; } ;
struct buffer {int len; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPTR (struct buffer*) ; 
 scalar_t__ PROTO_UDP ; 
 int SF_USE_IP_PKTINFO ; 
 int /*<<< orphan*/  addr_zero_host (TYPE_3__*) ; 
 scalar_t__ af_addr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_address_length (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  buf_forward_capacity (struct buffer*) ; 
 scalar_t__ link_socket_read_udp_posix_recvmsg (struct link_socket*,struct buffer*,struct link_socket_actual*) ; 
 int recvfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

int
link_socket_read_udp_posix(struct link_socket *sock,
                           struct buffer *buf,
                           struct link_socket_actual *from)
{
    socklen_t fromlen = sizeof(from->dest.addr);
    socklen_t expectedlen = af_addr_size(sock->info.af);
    addr_zero_host(&from->dest);
#if ENABLE_IP_PKTINFO
    /* Both PROTO_UDPv4 and PROTO_UDPv6 */
    if (sock->info.proto == PROTO_UDP && sock->sockflags & SF_USE_IP_PKTINFO)
    {
        fromlen = link_socket_read_udp_posix_recvmsg(sock, buf, from);
    }
    else
#endif
    buf->len = recvfrom(sock->sd, BPTR(buf), buf_forward_capacity(buf), 0,
                        &from->dest.addr.sa, &fromlen);
    /* FIXME: won't do anything when sock->info.af == AF_UNSPEC */
    if (buf->len >= 0 && expectedlen && fromlen != expectedlen)
    {
        bad_address_length(fromlen, expectedlen);
    }
    return buf->len;
}