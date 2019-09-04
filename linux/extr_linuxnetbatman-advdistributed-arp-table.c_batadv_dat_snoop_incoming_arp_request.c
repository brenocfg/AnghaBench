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
struct batadv_unicast_4addr_packet {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  distributed_arp_table; } ;
struct batadv_dat_entry {int /*<<< orphan*/  mac_addr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ ARPOP_REQUEST ; 
 int /*<<< orphan*/  BATADV_CNT_DAT_CACHED_REPLY_TX ; 
 int /*<<< orphan*/  BATADV_P_DAT_CACHE_REPLY ; 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_arp_get_type (struct batadv_priv*,struct sk_buff*,int) ; 
 int /*<<< orphan*/ * batadv_arp_hw_src (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_dst (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_src (struct sk_buff*,int) ; 
 struct sk_buff* batadv_dat_arp_create_reply (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_add (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 struct batadv_dat_entry* batadv_dat_entry_hash_find (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_put (struct batadv_dat_entry*) ; 
 unsigned short batadv_dat_get_vid (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  batadv_dbg_arp (struct batadv_priv*,struct sk_buff*,int,char*) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int batadv_send_skb_via_tt (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ *,unsigned short) ; 
 int batadv_send_skb_via_tt_4addr (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

bool batadv_dat_snoop_incoming_arp_request(struct batadv_priv *bat_priv,
					   struct sk_buff *skb, int hdr_size)
{
	u16 type;
	__be32 ip_src, ip_dst;
	u8 *hw_src;
	struct sk_buff *skb_new;
	struct batadv_dat_entry *dat_entry = NULL;
	bool ret = false;
	unsigned short vid;
	int err;

	if (!atomic_read(&bat_priv->distributed_arp_table))
		goto out;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	if (type != ARPOP_REQUEST)
		goto out;

	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_src = batadv_arp_ip_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing incoming ARP REQUEST");

	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);

	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_dst, vid);
	if (!dat_entry)
		goto out;

	skb_new = batadv_dat_arp_create_reply(bat_priv, ip_dst, ip_src,
					      dat_entry->mac_addr, hw_src, vid);
	if (!skb_new)
		goto out;

	/* To preserve backwards compatibility, the node has choose the outgoing
	 * format based on the incoming request packet type. The assumption is
	 * that a node not using the 4addr packet format doesn't support it.
	 */
	if (hdr_size == sizeof(struct batadv_unicast_4addr_packet))
		err = batadv_send_skb_via_tt_4addr(bat_priv, skb_new,
						   BATADV_P_DAT_CACHE_REPLY,
						   NULL, vid);
	else
		err = batadv_send_skb_via_tt(bat_priv, skb_new, NULL, vid);

	if (err != NET_XMIT_DROP) {
		batadv_inc_counter(bat_priv, BATADV_CNT_DAT_CACHED_REPLY_TX);
		ret = true;
	}
out:
	if (dat_entry)
		batadv_dat_entry_put(dat_entry);
	if (ret)
		kfree_skb(skb);
	return ret;
}