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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  distributed_arp_table; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ ARPOP_REPLY ; 
 int /*<<< orphan*/  BATADV_P_DAT_DHT_PUT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_arp_get_type (struct batadv_priv*,struct sk_buff*,int) ; 
 int /*<<< orphan*/ * batadv_arp_hw_dst (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * batadv_arp_hw_src (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_dst (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_src (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_dat_entry_add (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_forward_data (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short batadv_dat_get_vid (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  batadv_dbg_arp (struct batadv_priv*,struct sk_buff*,int,char*) ; 

void batadv_dat_snoop_outgoing_arp_reply(struct batadv_priv *bat_priv,
					 struct sk_buff *skb)
{
	u16 type;
	__be32 ip_src, ip_dst;
	u8 *hw_src, *hw_dst;
	int hdr_size = 0;
	unsigned short vid;

	if (!atomic_read(&bat_priv->distributed_arp_table))
		return;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	if (type != ARPOP_REPLY)
		return;

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing outgoing ARP REPLY");

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	hw_dst = batadv_arp_hw_dst(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);
	batadv_dat_entry_add(bat_priv, ip_dst, hw_dst, vid);

	/* Send the ARP reply to the candidates for both the IP addresses that
	 * the node obtained from the ARP reply
	 */
	batadv_dat_forward_data(bat_priv, skb, ip_src, vid,
				BATADV_P_DAT_DHT_PUT);
	batadv_dat_forward_data(bat_priv, skb, ip_dst, vid,
				BATADV_P_DAT_DHT_PUT);
}