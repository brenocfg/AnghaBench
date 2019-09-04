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
struct sk_buff {unsigned int len; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int /*<<< orphan*/  ptype_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_queue_xmit_nit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int netdev_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int) ; 
 int /*<<< orphan*/  ptype_all ; 
 int /*<<< orphan*/  trace_net_dev_start_xmit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  trace_net_dev_xmit (struct sk_buff*,int,struct net_device*,unsigned int) ; 

__attribute__((used)) static int xmit_one(struct sk_buff *skb, struct net_device *dev,
		    struct netdev_queue *txq, bool more)
{
	unsigned int len;
	int rc;

	if (!list_empty(&ptype_all) || !list_empty(&dev->ptype_all))
		dev_queue_xmit_nit(skb, dev);

	len = skb->len;
	trace_net_dev_start_xmit(skb, dev);
	rc = netdev_start_xmit(skb, dev, txq, more);
	trace_net_dev_xmit(skb, rc, dev, len);

	return rc;
}