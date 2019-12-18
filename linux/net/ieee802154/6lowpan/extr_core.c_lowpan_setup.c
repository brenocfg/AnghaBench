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
struct net_device {int hard_header_len; int flags; int needs_free_netdev; int /*<<< orphan*/  features; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  broadcast; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  lowpan_header_ops ; 
 int /*<<< orphan*/  lowpan_netdev_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lowpan_setup(struct net_device *ldev)
{
	memset(ldev->broadcast, 0xff, IEEE802154_ADDR_LEN);
	/* We need an ipv6hdr as minimum len when calling xmit */
	ldev->hard_header_len	= sizeof(struct ipv6hdr);
	ldev->flags		= IFF_BROADCAST | IFF_MULTICAST;
	ldev->priv_flags	|= IFF_NO_QUEUE;

	ldev->netdev_ops	= &lowpan_netdev_ops;
	ldev->header_ops	= &lowpan_header_ops;
	ldev->needs_free_netdev	= true;
	ldev->features		|= NETIF_F_NETNS_LOCAL;
}