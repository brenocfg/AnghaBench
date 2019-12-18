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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  xmit_work; int /*<<< orphan*/  xmit_queue; } ;
struct TYPE_2__ {int deferred_xmit; } ;

/* Variables and functions */
 TYPE_1__* DSA_SKB_CB (struct sk_buff*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void *dsa_defer_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);

	DSA_SKB_CB(skb)->deferred_xmit = true;

	skb_queue_tail(&dp->xmit_queue, skb);
	schedule_work(&dp->xmit_work);
	return NULL;
}