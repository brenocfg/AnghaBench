#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct udphdr {int dummy; } ;
struct net_device {int needs_free_netdev; int flags; scalar_t__ needed_headroom; int /*<<< orphan*/  features; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  type; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/ * netdev_ops; } ;
struct iphdr {int dummy; } ;
struct gtp0_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NONE ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int IFF_POINTOPOINT ; 
 scalar_t__ LL_MAX_HEADER ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  gtp_netdev_ops ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static void gtp_link_setup(struct net_device *dev)
{
	dev->netdev_ops		= &gtp_netdev_ops;
	dev->needs_free_netdev	= true;

	dev->hard_header_len = 0;
	dev->addr_len = 0;

	/* Zero header length. */
	dev->type = ARPHRD_NONE;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;

	dev->priv_flags	|= IFF_NO_QUEUE;
	dev->features	|= NETIF_F_LLTX;
	netif_keep_dst(dev);

	/* Assume largest header, ie. GTPv0. */
	dev->needed_headroom	= LL_MAX_HEADER +
				  sizeof(struct iphdr) +
				  sizeof(struct udphdr) +
				  sizeof(struct gtp0_header);
}