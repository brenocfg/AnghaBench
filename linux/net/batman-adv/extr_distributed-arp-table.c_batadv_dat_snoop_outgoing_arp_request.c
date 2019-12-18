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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  distributed_arp_table; struct net_device* soft_iface; } ;
struct batadv_dat_entry {int /*<<< orphan*/  mac_addr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ ARPOP_REQUEST ; 
 int /*<<< orphan*/  BATADV_CNT_RX ; 
 int /*<<< orphan*/  BATADV_CNT_RX_BYTES ; 
 int /*<<< orphan*/  BATADV_DBG_DAT ; 
 int /*<<< orphan*/  BATADV_P_DAT_DHT_GET ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_add_counter (struct batadv_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ batadv_arp_get_type (struct batadv_priv*,struct sk_buff*,int) ; 
 int /*<<< orphan*/ * batadv_arp_hw_src (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_dst (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_src (struct sk_buff*,int) ; 
 int /*<<< orphan*/  batadv_bla_check_claim (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 struct sk_buff* batadv_dat_arp_create_reply (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_add (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 struct batadv_dat_entry* batadv_dat_entry_hash_find (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_put (struct batadv_dat_entry*) ; 
 int batadv_dat_forward_data (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short batadv_dat_get_vid (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,...) ; 
 int /*<<< orphan*/  batadv_dbg_arp (struct batadv_priv*,struct sk_buff*,int,char*) ; 
 int /*<<< orphan*/  batadv_inc_counter (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ batadv_is_my_client (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

bool batadv_dat_snoop_outgoing_arp_request(struct batadv_priv *bat_priv,
					   struct sk_buff *skb)
{
	u16 type = 0;
	__be32 ip_dst, ip_src;
	u8 *hw_src;
	bool ret = false;
	struct batadv_dat_entry *dat_entry = NULL;
	struct sk_buff *skb_new;
	struct net_device *soft_iface = bat_priv->soft_iface;
	int hdr_size = 0;
	unsigned short vid;

	if (!atomic_read(&bat_priv->distributed_arp_table))
		goto out;

	vid = batadv_dat_get_vid(skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, skb, hdr_size);
	/* If the node gets an ARP_REQUEST it has to send a DHT_GET unicast
	 * message to the selected DHT candidates
	 */
	if (type != ARPOP_REQUEST)
		goto out;

	batadv_dbg_arp(bat_priv, skb, hdr_size, "Parsing outgoing ARP REQUEST");

	ip_src = batadv_arp_ip_src(skb, hdr_size);
	hw_src = batadv_arp_hw_src(skb, hdr_size);
	ip_dst = batadv_arp_ip_dst(skb, hdr_size);

	batadv_dat_entry_add(bat_priv, ip_src, hw_src, vid);

	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_dst, vid);
	if (dat_entry) {
		/* If the ARP request is destined for a local client the local
		 * client will answer itself. DAT would only generate a
		 * duplicate packet.
		 *
		 * Moreover, if the soft-interface is enslaved into a bridge, an
		 * additional DAT answer may trigger kernel warnings about
		 * a packet coming from the wrong port.
		 */
		if (batadv_is_my_client(bat_priv, dat_entry->mac_addr, vid)) {
			ret = true;
			goto out;
		}

		/* If BLA is enabled, only send ARP replies if we have claimed
		 * the destination for the ARP request or if no one else of
		 * the backbone gws belonging to our backbone has claimed the
		 * destination.
		 */
		if (!batadv_bla_check_claim(bat_priv,
					    dat_entry->mac_addr, vid)) {
			batadv_dbg(BATADV_DBG_DAT, bat_priv,
				   "Device %pM claimed by another backbone gw. Don't send ARP reply!",
				   dat_entry->mac_addr);
			ret = true;
			goto out;
		}

		skb_new = batadv_dat_arp_create_reply(bat_priv, ip_dst, ip_src,
						      dat_entry->mac_addr,
						      hw_src, vid);
		if (!skb_new)
			goto out;

		skb_new->protocol = eth_type_trans(skb_new, soft_iface);

		batadv_inc_counter(bat_priv, BATADV_CNT_RX);
		batadv_add_counter(bat_priv, BATADV_CNT_RX_BYTES,
				   skb->len + ETH_HLEN + hdr_size);

		netif_rx(skb_new);
		batadv_dbg(BATADV_DBG_DAT, bat_priv, "ARP request replied locally\n");
		ret = true;
	} else {
		/* Send the request to the DHT */
		ret = batadv_dat_forward_data(bat_priv, skb, ip_dst, vid,
					      BATADV_P_DAT_DHT_GET);
	}
out:
	if (dat_entry)
		batadv_dat_entry_put(dat_entry);
	return ret;
}