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
typedef  int u8 ;
struct sk_buff {int* data; scalar_t__ ip_summed; int offload_fwd_mark; int /*<<< orphan*/  csum; int /*<<< orphan*/  dev; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __wsum ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int* DSA_HLEN ; 
 int* EDSA_HLEN ; 
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int ETH_P_8021Q ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_master_find_slave (struct net_device*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *edsa_rcv(struct sk_buff *skb, struct net_device *dev,
				struct packet_type *pt)
{
	u8 *edsa_header;
	int source_device;
	int source_port;

	if (unlikely(!pskb_may_pull(skb, EDSA_HLEN)))
		return NULL;

	/*
	 * Skip the two null bytes after the ethertype.
	 */
	edsa_header = skb->data + 2;

	/*
	 * Check that frame type is either TO_CPU or FORWARD.
	 */
	if ((edsa_header[0] & 0xc0) != 0x00 && (edsa_header[0] & 0xc0) != 0xc0)
		return NULL;

	/*
	 * Determine source device and port.
	 */
	source_device = edsa_header[0] & 0x1f;
	source_port = (edsa_header[1] >> 3) & 0x1f;

	skb->dev = dsa_master_find_slave(dev, source_device, source_port);
	if (!skb->dev)
		return NULL;

	/*
	 * If the 'tagged' bit is set, convert the DSA tag to a 802.1q
	 * tag and delete the ethertype part.  If the 'tagged' bit is
	 * clear, delete the ethertype and the DSA tag parts.
	 */
	if (edsa_header[0] & 0x20) {
		u8 new_header[4];

		/*
		 * Insert 802.1q ethertype and copy the VLAN-related
		 * fields, but clear the bit that will hold CFI (since
		 * DSA uses that bit location for another purpose).
		 */
		new_header[0] = (ETH_P_8021Q >> 8) & 0xff;
		new_header[1] = ETH_P_8021Q & 0xff;
		new_header[2] = edsa_header[2] & ~0x10;
		new_header[3] = edsa_header[3];

		/*
		 * Move CFI bit from its place in the DSA header to
		 * its 802.1q-designated place.
		 */
		if (edsa_header[1] & 0x01)
			new_header[2] |= 0x10;

		skb_pull_rcsum(skb, DSA_HLEN);

		/*
		 * Update packet checksum if skb is CHECKSUM_COMPLETE.
		 */
		if (skb->ip_summed == CHECKSUM_COMPLETE) {
			__wsum c = skb->csum;
			c = csum_add(c, csum_partial(new_header + 2, 2, 0));
			c = csum_sub(c, csum_partial(edsa_header + 2, 2, 0));
			skb->csum = c;
		}

		memcpy(edsa_header, new_header, DSA_HLEN);

		memmove(skb->data - ETH_HLEN,
			skb->data - ETH_HLEN - DSA_HLEN,
			2 * ETH_ALEN);
	} else {
		/*
		 * Remove DSA tag and update checksum.
		 */
		skb_pull_rcsum(skb, EDSA_HLEN);
		memmove(skb->data - ETH_HLEN,
			skb->data - ETH_HLEN - EDSA_HLEN,
			2 * ETH_ALEN);
	}

	skb->offload_fwd_mark = 1;

	return skb;
}