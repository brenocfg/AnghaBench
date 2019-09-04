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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct hdlc_header {int /*<<< orphan*/  protocol; scalar_t__ control; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ CISCO_KEEPALIVE ; 
 int /*<<< orphan*/  CISCO_MULTICAST ; 
 int /*<<< orphan*/  CISCO_UNICAST ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int cisco_hard_header(struct sk_buff *skb, struct net_device *dev,
			     u16 type, const void *daddr, const void *saddr,
			     unsigned int len)
{
	struct hdlc_header *data;
#ifdef DEBUG_HARD_HEADER
	printk(KERN_DEBUG "%s: cisco_hard_header called\n", dev->name);
#endif

	skb_push(skb, sizeof(struct hdlc_header));
	data = (struct hdlc_header*)skb->data;
	if (type == CISCO_KEEPALIVE)
		data->address = CISCO_MULTICAST;
	else
		data->address = CISCO_UNICAST;
	data->control = 0;
	data->protocol = htons(type);

	return sizeof(struct hdlc_header);
}