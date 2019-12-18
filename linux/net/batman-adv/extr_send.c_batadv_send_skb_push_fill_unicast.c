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
struct sk_buff {scalar_t__ data; } ;
struct batadv_unicast_packet {int /*<<< orphan*/  ttvn; int /*<<< orphan*/  dest; int /*<<< orphan*/  ttl; int /*<<< orphan*/  packet_type; int /*<<< orphan*/  version; } ;
struct batadv_orig_node {int /*<<< orphan*/  orig; int /*<<< orphan*/  last_ttvn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_COMPAT_VERSION ; 
 int /*<<< orphan*/  BATADV_TTL ; 
 int /*<<< orphan*/  BATADV_UNICAST ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ batadv_skb_head_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
batadv_send_skb_push_fill_unicast(struct sk_buff *skb, int hdr_size,
				  struct batadv_orig_node *orig_node)
{
	struct batadv_unicast_packet *unicast_packet;
	u8 ttvn = (u8)atomic_read(&orig_node->last_ttvn);

	if (batadv_skb_head_push(skb, hdr_size) < 0)
		return false;

	unicast_packet = (struct batadv_unicast_packet *)skb->data;
	unicast_packet->version = BATADV_COMPAT_VERSION;
	/* batman packet type: unicast */
	unicast_packet->packet_type = BATADV_UNICAST;
	/* set unicast ttl */
	unicast_packet->ttl = BATADV_TTL;
	/* copy the destination for faster routing */
	ether_addr_copy(unicast_packet->dest, orig_node->orig);
	/* set the destination tt version number */
	unicast_packet->ttvn = ttvn;

	return true;
}