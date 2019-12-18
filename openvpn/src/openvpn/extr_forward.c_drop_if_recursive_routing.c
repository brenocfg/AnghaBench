#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_13__ {scalar_t__ sa_family; } ;
struct TYPE_11__ {scalar_t__ s_addr; } ;
struct TYPE_12__ {TYPE_2__ sin_addr; } ;
struct TYPE_15__ {TYPE_5__ in6; TYPE_4__ sa; TYPE_3__ in4; } ;
struct openvpn_sockaddr {TYPE_6__ addr; } ;
struct openvpn_ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct openvpn_iphdr {scalar_t__ daddr; } ;
struct gc_arena {int dummy; } ;
struct TYPE_18__ {scalar_t__ len; } ;
struct TYPE_16__ {TYPE_8__* to_link_addr; TYPE_9__ buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  tuntap; } ;
struct context {TYPE_7__ c2; TYPE_1__ c1; } ;
struct buffer {int dummy; } ;
struct TYPE_17__ {struct openvpn_sockaddr dest; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int BLEN (struct buffer*) ; 
 scalar_t__ BPTR (struct buffer*) ; 
 int /*<<< orphan*/  D_LOW ; 
 scalar_t__ IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUNNEL_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int get_tun_ip_ver (int /*<<< orphan*/ ,TYPE_9__*,int*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_link_socket_actual (TYPE_8__*,struct gc_arena*) ; 

__attribute__((used)) static void
drop_if_recursive_routing(struct context *c, struct buffer *buf)
{
    bool drop = false;
    struct openvpn_sockaddr tun_sa;
    int ip_hdr_offset = 0;

    if (c->c2.to_link_addr == NULL) /* no remote addr known */
    {
        return;
    }

    tun_sa = c->c2.to_link_addr->dest;

    int proto_ver = get_tun_ip_ver(TUNNEL_TYPE(c->c1.tuntap), &c->c2.buf, &ip_hdr_offset);

    if (proto_ver == 4)
    {
        const struct openvpn_iphdr *pip;

        /* make sure we got whole IP header */
        if (BLEN(buf) < ((int) sizeof(struct openvpn_iphdr) + ip_hdr_offset))
        {
            return;
        }

        /* skip ipv4 packets for ipv6 tun */
        if (tun_sa.addr.sa.sa_family != AF_INET)
        {
            return;
        }

        pip = (struct openvpn_iphdr *) (BPTR(buf) + ip_hdr_offset);

        /* drop packets with same dest addr as gateway */
        if (tun_sa.addr.in4.sin_addr.s_addr == pip->daddr)
        {
            drop = true;
        }
    }
    else if (proto_ver == 6)
    {
        const struct openvpn_ipv6hdr *pip6;

        /* make sure we got whole IPv6 header */
        if (BLEN(buf) < ((int) sizeof(struct openvpn_ipv6hdr) + ip_hdr_offset))
        {
            return;
        }

        /* skip ipv6 packets for ipv4 tun */
        if (tun_sa.addr.sa.sa_family != AF_INET6)
        {
            return;
        }

        /* drop packets with same dest addr as gateway */
        pip6 = (struct openvpn_ipv6hdr *) (BPTR(buf) + ip_hdr_offset);
        if (IN6_ARE_ADDR_EQUAL(&tun_sa.addr.in6.sin6_addr, &pip6->daddr))
        {
            drop = true;
        }
    }

    if (drop)
    {
        struct gc_arena gc = gc_new();

        c->c2.buf.len = 0;

        msg(D_LOW, "Recursive routing detected, drop tun packet to %s",
            print_link_socket_actual(c->c2.to_link_addr, &gc));
        gc_free(&gc);
    }
}