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
struct udp_tunnel_info {unsigned short type; int /*<<< orphan*/  port; int /*<<< orphan*/  sa_family; } ;
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_family; } ;
struct net_device {int features; TYPE_1__* netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  inet_sport; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ndo_udp_tunnel_del ) (struct net_device*,struct udp_tunnel_info*) ;} ;

/* Variables and functions */
 int NETIF_F_RX_UDP_TUNNEL_PORT ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct udp_tunnel_info*) ; 

void udp_tunnel_drop_rx_port(struct net_device *dev, struct socket *sock,
			     unsigned short type)
{
	struct sock *sk = sock->sk;
	struct udp_tunnel_info ti;

	if (!dev->netdev_ops->ndo_udp_tunnel_del ||
	    !(dev->features & NETIF_F_RX_UDP_TUNNEL_PORT))
		return;

	ti.type = type;
	ti.sa_family = sk->sk_family;
	ti.port = inet_sk(sk)->inet_sport;

	dev->netdev_ops->ndo_udp_tunnel_del(dev, &ti);
}