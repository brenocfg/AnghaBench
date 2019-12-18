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
struct sk_buff {scalar_t__ protocol; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  rx_handler_data; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_PAE ; 
 int /*<<< orphan*/  RX_HANDLER_CONSUMED ; 
 int /*<<< orphan*/  RX_HANDLER_PASS ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_forward_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

rx_handler_result_t trelay_handle_frame(struct sk_buff **pskb)
{
	struct net_device *dev;
	struct sk_buff *skb = *pskb;

	dev = rcu_dereference(skb->dev->rx_handler_data);
	if (!dev)
		return RX_HANDLER_PASS;

	if (skb->protocol == htons(ETH_P_PAE))
		return RX_HANDLER_PASS;

	skb_push(skb, ETH_HLEN);
	skb->dev = dev;
	skb_forward_csum(skb);
	dev_queue_xmit(skb);

	return RX_HANDLER_CONSUMED;
}