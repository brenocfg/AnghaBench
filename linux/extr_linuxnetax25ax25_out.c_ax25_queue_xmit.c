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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_fwd_dev (struct net_device*) ; 
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 

void ax25_queue_xmit(struct sk_buff *skb, struct net_device *dev)
{
	unsigned char *ptr;

	skb->protocol = ax25_type_trans(skb, ax25_fwd_dev(dev));

	ptr  = skb_push(skb, 1);
	*ptr = 0x00;			/* KISS */

	dev_queue_xmit(skb);
}