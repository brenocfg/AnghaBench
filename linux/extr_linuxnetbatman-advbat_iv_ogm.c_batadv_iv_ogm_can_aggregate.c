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
struct batadv_priv {int dummy; } ;
struct batadv_ogm_packet {int flags; int ttl; } ;
typedef  struct batadv_hard_iface const batadv_hard_iface ;
struct batadv_forw_packet {int packet_len; struct batadv_hard_iface const* if_incoming; scalar_t__ own; struct batadv_hard_iface const* if_outgoing; int /*<<< orphan*/  send_time; TYPE_1__* skb; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int BATADV_DIRECTLINK ; 
 int BATADV_MAX_AGGREGATION_BYTES ; 
 int /*<<< orphan*/  BATADV_MAX_AGGREGATION_MS ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface const*) ; 
 struct batadv_hard_iface const* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_before (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
batadv_iv_ogm_can_aggregate(const struct batadv_ogm_packet *new_bat_ogm_packet,
			    struct batadv_priv *bat_priv,
			    int packet_len, unsigned long send_time,
			    bool directlink,
			    const struct batadv_hard_iface *if_incoming,
			    const struct batadv_hard_iface *if_outgoing,
			    const struct batadv_forw_packet *forw_packet)
{
	struct batadv_ogm_packet *batadv_ogm_packet;
	int aggregated_bytes = forw_packet->packet_len + packet_len;
	struct batadv_hard_iface *primary_if = NULL;
	bool res = false;
	unsigned long aggregation_end_time;

	batadv_ogm_packet = (struct batadv_ogm_packet *)forw_packet->skb->data;
	aggregation_end_time = send_time;
	aggregation_end_time += msecs_to_jiffies(BATADV_MAX_AGGREGATION_MS);

	/* we can aggregate the current packet to this aggregated packet
	 * if:
	 *
	 * - the send time is within our MAX_AGGREGATION_MS time
	 * - the resulting packet wont be bigger than
	 *   MAX_AGGREGATION_BYTES
	 * otherwise aggregation is not possible
	 */
	if (!time_before(send_time, forw_packet->send_time) ||
	    !time_after_eq(aggregation_end_time, forw_packet->send_time))
		return false;

	if (aggregated_bytes > BATADV_MAX_AGGREGATION_BYTES)
		return false;

	/* packet is not leaving on the same interface. */
	if (forw_packet->if_outgoing != if_outgoing)
		return false;

	/* check aggregation compatibility
	 * -> direct link packets are broadcasted on
	 *    their interface only
	 * -> aggregate packet if the current packet is
	 *    a "global" packet as well as the base
	 *    packet
	 */
	primary_if = batadv_primary_if_get_selected(bat_priv);
	if (!primary_if)
		return false;

	/* packets without direct link flag and high TTL
	 * are flooded through the net
	 */
	if (!directlink &&
	    !(batadv_ogm_packet->flags & BATADV_DIRECTLINK) &&
	    batadv_ogm_packet->ttl != 1 &&

	    /* own packets originating non-primary
	     * interfaces leave only that interface
	     */
	    (!forw_packet->own ||
	     forw_packet->if_incoming == primary_if)) {
		res = true;
		goto out;
	}

	/* if the incoming packet is sent via this one
	 * interface only - we still can aggregate
	 */
	if (directlink &&
	    new_bat_ogm_packet->ttl == 1 &&
	    forw_packet->if_incoming == if_incoming &&

	    /* packets from direct neighbors or
	     * own secondary interface packets
	     * (= secondary interface packets in general)
	     */
	    (batadv_ogm_packet->flags & BATADV_DIRECTLINK ||
	     (forw_packet->own &&
	      forw_packet->if_incoming != primary_if))) {
		res = true;
		goto out;
	}

out:
	if (primary_if)
		batadv_hardif_put(primary_if);
	return res;
}