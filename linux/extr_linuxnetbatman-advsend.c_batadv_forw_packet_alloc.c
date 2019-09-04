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
struct sk_buff {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  batman_queue_left; int /*<<< orphan*/  bcast_queue_left; } ;
struct batadv_hard_iface {int /*<<< orphan*/  refcount; } ;
struct batadv_forw_packet {scalar_t__ num_packets; struct batadv_hard_iface* if_outgoing; struct batadv_hard_iface* if_incoming; int /*<<< orphan*/ * queue_left; struct sk_buff* skb; int /*<<< orphan*/  cleanup_list; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_atomic_dec_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,char const*) ; 
 struct batadv_forw_packet* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

struct batadv_forw_packet *
batadv_forw_packet_alloc(struct batadv_hard_iface *if_incoming,
			 struct batadv_hard_iface *if_outgoing,
			 atomic_t *queue_left,
			 struct batadv_priv *bat_priv,
			 struct sk_buff *skb)
{
	struct batadv_forw_packet *forw_packet;
	const char *qname;

	if (queue_left && !batadv_atomic_dec_not_zero(queue_left)) {
		qname = "unknown";

		if (queue_left == &bat_priv->bcast_queue_left)
			qname = "bcast";

		if (queue_left == &bat_priv->batman_queue_left)
			qname = "batman";

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "%s queue is full\n", qname);

		return NULL;
	}

	forw_packet = kmalloc(sizeof(*forw_packet), GFP_ATOMIC);
	if (!forw_packet)
		goto err;

	if (if_incoming)
		kref_get(&if_incoming->refcount);

	if (if_outgoing)
		kref_get(&if_outgoing->refcount);

	INIT_HLIST_NODE(&forw_packet->list);
	INIT_HLIST_NODE(&forw_packet->cleanup_list);
	forw_packet->skb = skb;
	forw_packet->queue_left = queue_left;
	forw_packet->if_incoming = if_incoming;
	forw_packet->if_outgoing = if_outgoing;
	forw_packet->num_packets = 0;

	return forw_packet;

err:
	if (queue_left)
		atomic_inc(queue_left);

	return NULL;
}