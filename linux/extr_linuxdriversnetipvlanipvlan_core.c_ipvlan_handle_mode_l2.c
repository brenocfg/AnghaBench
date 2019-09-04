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
struct ipvl_port {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RX_HANDLER_PASS ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ipvlan_external_frame (struct sk_buff*,struct ipvl_port*) ; 
 int /*<<< orphan*/  ipvlan_handle_mode_l3 (struct sk_buff**,struct ipvl_port*) ; 
 int /*<<< orphan*/  ipvlan_multicast_enqueue (struct ipvl_port*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  ipvlan_skb_crossing_ns (struct sk_buff*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rx_handler_result_t ipvlan_handle_mode_l2(struct sk_buff **pskb,
						 struct ipvl_port *port)
{
	struct sk_buff *skb = *pskb;
	struct ethhdr *eth = eth_hdr(skb);
	rx_handler_result_t ret = RX_HANDLER_PASS;

	if (is_multicast_ether_addr(eth->h_dest)) {
		if (ipvlan_external_frame(skb, port)) {
			struct sk_buff *nskb = skb_clone(skb, GFP_ATOMIC);

			/* External frames are queued for device local
			 * distribution, but a copy is given to master
			 * straight away to avoid sending duplicates later
			 * when work-queue processes this frame. This is
			 * achieved by returning RX_HANDLER_PASS.
			 */
			if (nskb) {
				ipvlan_skb_crossing_ns(nskb, NULL);
				ipvlan_multicast_enqueue(port, nskb, false);
			}
		}
	} else {
		/* Perform like l3 mode for non-multicast packet */
		ret = ipvlan_handle_mode_l3(pskb, port);
	}

	return ret;
}