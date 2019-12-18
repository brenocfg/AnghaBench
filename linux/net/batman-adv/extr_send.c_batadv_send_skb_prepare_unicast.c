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
struct batadv_unicast_packet {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
 int batadv_send_skb_push_fill_unicast (struct sk_buff*,size_t,struct batadv_orig_node*) ; 

__attribute__((used)) static bool batadv_send_skb_prepare_unicast(struct sk_buff *skb,
					    struct batadv_orig_node *orig_node)
{
	size_t uni_size = sizeof(struct batadv_unicast_packet);

	return batadv_send_skb_push_fill_unicast(skb, uni_size, orig_node);
}