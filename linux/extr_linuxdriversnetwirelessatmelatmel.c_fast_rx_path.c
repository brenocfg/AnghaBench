#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;
struct atmel_private {TYPE_2__* dev; scalar_t__ do_rx_crc; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 size_t ETH_ALEN ; 
 int IEEE80211_FCTL_FROMDS ; 
 int /*<<< orphan*/  atmel_copy_to_host (TYPE_2__*,void*,int,int) ; 
 int crc32_le (int,unsigned char*,int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void fast_rx_path(struct atmel_private *priv,
			 struct ieee80211_hdr *header,
			 u16 msdu_size, u16 rx_packet_loc, u32 crc)
{
	/* fast path: unfragmented packet copy directly into skbuf */
	u8 mac4[6];
	struct sk_buff	*skb;
	unsigned char *skbp;

	/* get the final, mac 4 header field, this tells us encapsulation */
	atmel_copy_to_host(priv->dev, mac4, rx_packet_loc + 24, 6);
	msdu_size -= 6;

	if (priv->do_rx_crc) {
		crc = crc32_le(crc, mac4, 6);
		msdu_size -= 4;
	}

	if (!(skb = dev_alloc_skb(msdu_size + 14))) {
		priv->dev->stats.rx_dropped++;
		return;
	}

	skb_reserve(skb, 2);
	skbp = skb_put(skb, msdu_size + 12);
	atmel_copy_to_host(priv->dev, skbp + 12, rx_packet_loc + 30, msdu_size);

	if (priv->do_rx_crc) {
		u32 netcrc;
		crc = crc32_le(crc, skbp + 12, msdu_size);
		atmel_copy_to_host(priv->dev, (void *)&netcrc, rx_packet_loc + 30 + msdu_size, 4);
		if ((crc ^ 0xffffffff) != netcrc) {
			priv->dev->stats.rx_crc_errors++;
			dev_kfree_skb(skb);
			return;
		}
	}

	memcpy(skbp, header->addr1, ETH_ALEN); /* destination address */
	if (le16_to_cpu(header->frame_control) & IEEE80211_FCTL_FROMDS)
		memcpy(&skbp[ETH_ALEN], header->addr3, ETH_ALEN);
	else
		memcpy(&skbp[ETH_ALEN], header->addr2, ETH_ALEN); /* source address */

	skb->protocol = eth_type_trans(skb, priv->dev);
	skb->ip_summed = CHECKSUM_NONE;
	netif_rx(skb);
	priv->dev->stats.rx_bytes += 12 + msdu_size;
	priv->dev->stats.rx_packets++;
}