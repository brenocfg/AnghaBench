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
struct batadv_forw_packet {scalar_t__ queue_left; scalar_t__ if_outgoing; scalar_t__ if_incoming; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  batadv_hardif_put (scalar_t__) ; 
 int /*<<< orphan*/  consume_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct batadv_forw_packet*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 

void batadv_forw_packet_free(struct batadv_forw_packet *forw_packet,
			     bool dropped)
{
	if (dropped)
		kfree_skb(forw_packet->skb);
	else
		consume_skb(forw_packet->skb);

	if (forw_packet->if_incoming)
		batadv_hardif_put(forw_packet->if_incoming);
	if (forw_packet->if_outgoing)
		batadv_hardif_put(forw_packet->if_outgoing);
	if (forw_packet->queue_left)
		atomic_inc(forw_packet->queue_left);
	kfree(forw_packet);
}