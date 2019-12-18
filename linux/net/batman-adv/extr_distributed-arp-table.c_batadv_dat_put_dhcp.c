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
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_DAT ; 
 int /*<<< orphan*/  BATADV_P_DAT_DHT_PUT ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 struct sk_buff* batadv_dat_arp_create_reply (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_add (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_forward_data (struct batadv_priv*,struct sk_buff*,int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_print_vid (unsigned short) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_dat_put_dhcp(struct batadv_priv *bat_priv, u8 *chaddr,
				__be32 yiaddr, u8 *hw_dst, __be32 ip_dst,
				unsigned short vid)
{
	struct sk_buff *skb;

	skb = batadv_dat_arp_create_reply(bat_priv, yiaddr, ip_dst, chaddr,
					  hw_dst, vid);
	if (!skb)
		return;

	skb_set_network_header(skb, ETH_HLEN);

	batadv_dat_entry_add(bat_priv, yiaddr, chaddr, vid);
	batadv_dat_entry_add(bat_priv, ip_dst, hw_dst, vid);

	batadv_dat_forward_data(bat_priv, skb, yiaddr, vid,
				BATADV_P_DAT_DHT_PUT);
	batadv_dat_forward_data(bat_priv, skb, ip_dst, vid,
				BATADV_P_DAT_DHT_PUT);

	consume_skb(skb);

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from outgoing DHCPACK (server address): %pI4, %pM (vid: %i)\n",
		   &ip_dst, hw_dst, batadv_print_vid(vid));
	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "Snooped from outgoing DHCPACK (client address): %pI4, %pM (vid: %i)\n",
		   &yiaddr, chaddr, batadv_print_vid(vid));
}