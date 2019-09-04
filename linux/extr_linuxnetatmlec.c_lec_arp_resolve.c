#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lec_priv {int lane_version; scalar_t__ maximum_unknown_frame_count; int /*<<< orphan*/  lec_arp_lock; struct atm_vcc* mcast_vcc; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; void* expires; } ;
struct lec_arp_table {scalar_t__ status; int no_tries; scalar_t__ packets_flooded; int is_rdesc; TYPE_1__ timer; void* timestamp; void* last_used; struct atm_vcc* vcc; } ;
struct atm_vcc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ESI_ARP_PENDING ; 
 scalar_t__ ESI_FLUSH_PENDING ; 
 scalar_t__ ESI_FORWARD_DIRECT ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_mac ; 
 int /*<<< orphan*/  ether_addr_equal (unsigned char const*,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  l_arp_xmt ; 
 int /*<<< orphan*/  l_rdesc_arp_xmt ; 
 int /*<<< orphan*/  lec_arp_add (struct lec_priv*,struct lec_arp_table*) ; 
 int /*<<< orphan*/  lec_arp_expire_arp ; 
 struct lec_arp_table* lec_arp_find (struct lec_priv*,unsigned char const*) ; 
 int /*<<< orphan*/  lec_arp_hold (struct lec_arp_table*) ; 
 struct lec_arp_table* make_entry (struct lec_priv*,unsigned char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  send_to_lecd (struct lec_priv*,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct atm_vcc *lec_arp_resolve(struct lec_priv *priv,
				       const unsigned char *mac_to_find,
				       int is_rdesc,
				       struct lec_arp_table **ret_entry)
{
	unsigned long flags;
	struct lec_arp_table *entry;
	struct atm_vcc *found;

	if (mac_to_find[0] & 0x01) {
		switch (priv->lane_version) {
		case 1:
			return priv->mcast_vcc;
		case 2:	/* LANE2 wants arp for multicast addresses */
			if (ether_addr_equal(mac_to_find, bus_mac))
				return priv->mcast_vcc;
			break;
		default:
			break;
		}
	}

	spin_lock_irqsave(&priv->lec_arp_lock, flags);
	entry = lec_arp_find(priv, mac_to_find);

	if (entry) {
		if (entry->status == ESI_FORWARD_DIRECT) {
			/* Connection Ok */
			entry->last_used = jiffies;
			lec_arp_hold(entry);
			*ret_entry = entry;
			found = entry->vcc;
			goto out;
		}
		/*
		 * If the LE_ARP cache entry is still pending, reset count to 0
		 * so another LE_ARP request can be made for this frame.
		 */
		if (entry->status == ESI_ARP_PENDING)
			entry->no_tries = 0;
		/*
		 * Data direct VC not yet set up, check to see if the unknown
		 * frame count is greater than the limit. If the limit has
		 * not been reached, allow the caller to send packet to
		 * BUS.
		 */
		if (entry->status != ESI_FLUSH_PENDING &&
		    entry->packets_flooded <
		    priv->maximum_unknown_frame_count) {
			entry->packets_flooded++;
			pr_debug("Flooding..\n");
			found = priv->mcast_vcc;
			goto out;
		}
		/*
		 * We got here because entry->status == ESI_FLUSH_PENDING
		 * or BUS flood limit was reached for an entry which is
		 * in ESI_ARP_PENDING or ESI_VC_PENDING state.
		 */
		lec_arp_hold(entry);
		*ret_entry = entry;
		pr_debug("entry->status %d entry->vcc %p\n", entry->status,
			 entry->vcc);
		found = NULL;
	} else {
		/* No matching entry was found */
		entry = make_entry(priv, mac_to_find);
		pr_debug("Making entry\n");
		if (!entry) {
			found = priv->mcast_vcc;
			goto out;
		}
		lec_arp_add(priv, entry);
		/* We want arp-request(s) to be sent */
		entry->packets_flooded = 1;
		entry->status = ESI_ARP_PENDING;
		entry->no_tries = 1;
		entry->last_used = entry->timestamp = jiffies;
		entry->is_rdesc = is_rdesc;
		if (entry->is_rdesc)
			send_to_lecd(priv, l_rdesc_arp_xmt, mac_to_find, NULL,
				     NULL);
		else
			send_to_lecd(priv, l_arp_xmt, mac_to_find, NULL, NULL);
		entry->timer.expires = jiffies + (1 * HZ);
		entry->timer.function = lec_arp_expire_arp;
		add_timer(&entry->timer);
		found = priv->mcast_vcc;
	}

out:
	spin_unlock_irqrestore(&priv->lec_arp_lock, flags);
	return found;
}