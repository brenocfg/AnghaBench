#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ ax25_dev ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void ax25_kiss_cmd(ax25_dev *ax25_dev, unsigned char cmd, unsigned char param)
{
	struct sk_buff *skb;
	unsigned char *p;

	if (ax25_dev->dev == NULL)
		return;

	if ((skb = alloc_skb(2, GFP_ATOMIC)) == NULL)
		return;

	skb_reset_network_header(skb);
	p = skb_put(skb, 2);

	*p++ = cmd;
	*p++ = param;

	skb->protocol = ax25_type_trans(skb, ax25_dev->dev);

	dev_queue_xmit(skb);
}