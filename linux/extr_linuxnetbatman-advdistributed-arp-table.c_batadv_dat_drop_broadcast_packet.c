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
typedef  scalar_t__ u16 ;
struct batadv_priv {int /*<<< orphan*/  distributed_arp_table; } ;
struct batadv_forw_packet {int /*<<< orphan*/  skb; } ;
struct batadv_dat_entry {int dummy; } ;
struct batadv_bcast_packet {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ ARPOP_REQUEST ; 
 int /*<<< orphan*/  BATADV_DBG_DAT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_arp_get_type (struct batadv_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  batadv_arp_ip_dst (int /*<<< orphan*/ ,int) ; 
 struct batadv_dat_entry* batadv_dat_entry_hash_find (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  batadv_dat_entry_put (struct batadv_dat_entry*) ; 
 unsigned short batadv_dat_get_vid (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_forw_packet_is_rebroadcast (struct batadv_forw_packet*) ; 

bool batadv_dat_drop_broadcast_packet(struct batadv_priv *bat_priv,
				      struct batadv_forw_packet *forw_packet)
{
	u16 type;
	__be32 ip_dst;
	struct batadv_dat_entry *dat_entry = NULL;
	bool ret = false;
	int hdr_size = sizeof(struct batadv_bcast_packet);
	unsigned short vid;

	if (!atomic_read(&bat_priv->distributed_arp_table))
		goto out;

	/* If this packet is an ARP_REQUEST and the node already has the
	 * information that it is going to ask, then the packet can be dropped
	 */
	if (batadv_forw_packet_is_rebroadcast(forw_packet))
		goto out;

	vid = batadv_dat_get_vid(forw_packet->skb, &hdr_size);

	type = batadv_arp_get_type(bat_priv, forw_packet->skb, hdr_size);
	if (type != ARPOP_REQUEST)
		goto out;

	ip_dst = batadv_arp_ip_dst(forw_packet->skb, hdr_size);
	dat_entry = batadv_dat_entry_hash_find(bat_priv, ip_dst, vid);
	/* check if the node already got this entry */
	if (!dat_entry) {
		batadv_dbg(BATADV_DBG_DAT, bat_priv,
			   "ARP Request for %pI4: fallback\n", &ip_dst);
		goto out;
	}

	batadv_dbg(BATADV_DBG_DAT, bat_priv,
		   "ARP Request for %pI4: fallback prevented\n", &ip_dst);
	ret = true;

out:
	if (dat_entry)
		batadv_dat_entry_put(dat_entry);
	return ret;
}