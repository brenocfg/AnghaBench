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
struct sk_buff {int offload_fwd_mark; scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_master_find_slave (struct net_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *ksz_common_rcv(struct sk_buff *skb,
				      struct net_device *dev,
				      unsigned int port, unsigned int len)
{
	skb->dev = dsa_master_find_slave(dev, 0, port);
	if (!skb->dev)
		return NULL;

	pskb_trim_rcsum(skb, skb->len - len);

	skb->offload_fwd_mark = true;

	return skb;
}