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
struct sk_buff {int /*<<< orphan*/  pkt_type; struct net_device* dev; scalar_t__ data; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; } ;
struct TYPE_5__ {int /*<<< orphan*/  ethertype; } ;
struct TYPE_4__ {int dsap; } ;
struct TYPE_6__ {TYPE_2__ llc_snap; TYPE_1__ llc_8022_1; } ;
struct fddihdr {int* daddr; TYPE_3__ hdr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_2 ; 
 scalar_t__ FDDI_K_8022_HLEN ; 
 int /*<<< orphan*/  FDDI_K_ALEN ; 
 scalar_t__ FDDI_K_SNAP_HLEN ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_MULTICAST ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__be16 fddi_type_trans(struct sk_buff *skb, struct net_device *dev)
{
	struct fddihdr *fddi = (struct fddihdr *)skb->data;
	__be16 type;

	/*
	 * Set mac.raw field to point to FC byte, set data field to point
	 * to start of packet data.  Assume 802.2 SNAP frames for now.
	 */

	skb->dev = dev;
	skb_reset_mac_header(skb);	/* point to frame control (FC) */

	if(fddi->hdr.llc_8022_1.dsap==0xe0)
	{
		skb_pull(skb, FDDI_K_8022_HLEN-3);
		type = htons(ETH_P_802_2);
	}
	else
	{
		skb_pull(skb, FDDI_K_SNAP_HLEN);		/* adjust for 21 byte header */
		type=fddi->hdr.llc_snap.ethertype;
	}

	/* Set packet type based on destination address and flag settings */

	if (*fddi->daddr & 0x01)
	{
		if (memcmp(fddi->daddr, dev->broadcast, FDDI_K_ALEN) == 0)
			skb->pkt_type = PACKET_BROADCAST;
		else
			skb->pkt_type = PACKET_MULTICAST;
	}

	else if (dev->flags & IFF_PROMISC)
	{
		if (memcmp(fddi->daddr, dev->dev_addr, FDDI_K_ALEN))
			skb->pkt_type = PACKET_OTHERHOST;
	}

	/* Assume 802.2 SNAP frames, for now */

	return type;
}