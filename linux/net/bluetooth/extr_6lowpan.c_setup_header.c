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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct lowpan_peer {TYPE_1__* chan; int /*<<< orphan*/ * lladdr; } ;
struct lowpan_btle_dev {TYPE_2__* netdev; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  ipv6_daddr ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 struct lowpan_btle_dev* lowpan_btle_dev (struct net_device*) ; 
 TYPE_3__* lowpan_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  lowpan_header_compress (struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ *,int) ; 
 struct lowpan_peer* peer_lookup_dst (struct lowpan_btle_dev*,struct in6_addr*,struct sk_buff*) ; 

__attribute__((used)) static int setup_header(struct sk_buff *skb, struct net_device *netdev,
			bdaddr_t *peer_addr, u8 *peer_addr_type)
{
	struct in6_addr ipv6_daddr;
	struct ipv6hdr *hdr;
	struct lowpan_btle_dev *dev;
	struct lowpan_peer *peer;
	u8 *daddr;
	int err, status = 0;

	hdr = ipv6_hdr(skb);

	dev = lowpan_btle_dev(netdev);

	memcpy(&ipv6_daddr, &hdr->daddr, sizeof(ipv6_daddr));

	if (ipv6_addr_is_multicast(&ipv6_daddr)) {
		lowpan_cb(skb)->chan = NULL;
		daddr = NULL;
	} else {
		BT_DBG("dest IP %pI6c", &ipv6_daddr);

		/* The packet might be sent to 6lowpan interface
		 * because of routing (either via default route
		 * or user set route) so get peer according to
		 * the destination address.
		 */
		peer = peer_lookup_dst(dev, &ipv6_daddr, skb);
		if (!peer) {
			BT_DBG("no such peer");
			return -ENOENT;
		}

		daddr = peer->lladdr;
		*peer_addr = peer->chan->dst;
		*peer_addr_type = peer->chan->dst_type;
		lowpan_cb(skb)->chan = peer->chan;

		status = 1;
	}

	lowpan_header_compress(skb, netdev, daddr, dev->netdev->dev_addr);

	err = dev_hard_header(skb, netdev, ETH_P_IPV6, NULL, NULL, 0);
	if (err < 0)
		return err;

	return status;
}