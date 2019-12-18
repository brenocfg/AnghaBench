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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ethhdr {int /*<<< orphan*/ * h_source; int /*<<< orphan*/  h_proto; } ;
struct batadv_priv {int /*<<< orphan*/  distributed_arp_table; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_DAT ; 
 int BATADV_DHCP_CHADDR_LEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dat_check_dhcp_ack (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dat_entry_add (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 unsigned short batadv_dat_get_vid (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_print_vid (unsigned short) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void batadv_dat_snoop_incoming_dhcp_ack(struct batadv_priv *bat_priv,
					struct sk_buff *skb, int hdr_size)
{
	u8 chaddr[BATADV_DHCP_CHADDR_LEN];
	struct ethhdr *ethhdr;
	__be32 ip_src, yiaddr;
	unsigned short vid;
	__be16 proto;
	u8 *hw_src;

	if (!atomic_read(&bat_priv->distributed_arp_table))
		return;

	if (unlikely(!pskb_may_pull(skb, hdr_size + ETH_HLEN)))
		return;

	ethhdr = (struct ethhdr *)(skb->data + hdr_size);
	skb_set_network_header(skb, hdr_size + ETH_HLEN);
	proto = ethhdr->h_proto;

	if (!batadv_dat_check_dhcp_ack(skb, proto, &ip_src, chaddr, &yiaddr))
		return;

	hw_src = ethhdr->h_source;
	vid = batadv_dat_get_vid(skb, &hdr_size);

	batadv_dat_entry_add(bat_priv, yiaddr, chaddr, vid);
	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from incoming DHCPACK (server address): %pI4, %pM (vid: %i)\n",
		   &ip_src, hw_src, batadv_print_vid(vid));
	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from incoming DHCPACK (client address): %pI4, %pM (vid: %i)\n",
		   &yiaddr, chaddr, batadv_print_vid(vid));
}