#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  aggregated_ogms; int /*<<< orphan*/  batman_queue_left; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;
struct batadv_forw_packet {int packet_len; int own; int direct_link_flags; unsigned long send_time; int /*<<< orphan*/  delayed_work; TYPE_1__* skb; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_3__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int BATADV_MAX_AGGREGATION_BYTES ; 
 int BATADV_NO_FLAGS ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_forw_packet* batadv_forw_packet_alloc (struct batadv_hard_iface*,struct batadv_hard_iface*,int /*<<< orphan*/ *,struct batadv_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  batadv_forw_packet_ogmv1_queue (struct batadv_priv*,struct batadv_forw_packet*,unsigned long) ; 
 int /*<<< orphan*/  batadv_iv_send_outstanding_bat_ogm_packet ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ *,unsigned int) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 unsigned char* skb_put (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_reserve (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void batadv_iv_ogm_aggregate_new(const unsigned char *packet_buff,
					int packet_len, unsigned long send_time,
					bool direct_link,
					struct batadv_hard_iface *if_incoming,
					struct batadv_hard_iface *if_outgoing,
					int own_packet)
{
	struct batadv_priv *bat_priv = netdev_priv(if_incoming->soft_iface);
	struct batadv_forw_packet *forw_packet_aggr;
	struct sk_buff *skb;
	unsigned char *skb_buff;
	unsigned int skb_size;
	atomic_t *queue_left = own_packet ? NULL : &bat_priv->batman_queue_left;

	if (atomic_read(&bat_priv->aggregated_ogms) &&
	    packet_len < BATADV_MAX_AGGREGATION_BYTES)
		skb_size = BATADV_MAX_AGGREGATION_BYTES;
	else
		skb_size = packet_len;

	skb_size += ETH_HLEN;

	skb = netdev_alloc_skb_ip_align(NULL, skb_size);
	if (!skb)
		return;

	forw_packet_aggr = batadv_forw_packet_alloc(if_incoming, if_outgoing,
						    queue_left, bat_priv, skb);
	if (!forw_packet_aggr) {
		kfree_skb(skb);
		return;
	}

	forw_packet_aggr->skb->priority = TC_PRIO_CONTROL;
	skb_reserve(forw_packet_aggr->skb, ETH_HLEN);

	skb_buff = skb_put(forw_packet_aggr->skb, packet_len);
	forw_packet_aggr->packet_len = packet_len;
	memcpy(skb_buff, packet_buff, packet_len);

	forw_packet_aggr->own = own_packet;
	forw_packet_aggr->direct_link_flags = BATADV_NO_FLAGS;
	forw_packet_aggr->send_time = send_time;

	/* save packet direct link flag status */
	if (direct_link)
		forw_packet_aggr->direct_link_flags |= 1;

	INIT_DELAYED_WORK(&forw_packet_aggr->delayed_work,
			  batadv_iv_send_outstanding_bat_ogm_packet);

	batadv_forw_packet_ogmv1_queue(bat_priv, forw_packet_aggr, send_time);
}