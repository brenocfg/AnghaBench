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
typedef  int u8 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_master_find_slave (struct net_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *trailer_rcv(struct sk_buff *skb, struct net_device *dev,
				   struct packet_type *pt)
{
	u8 *trailer;
	int source_port;

	if (skb_linearize(skb))
		return NULL;

	trailer = skb_tail_pointer(skb) - 4;
	if (trailer[0] != 0x80 || (trailer[1] & 0xf8) != 0x00 ||
	    (trailer[2] & 0xef) != 0x00 || trailer[3] != 0x00)
		return NULL;

	source_port = trailer[1] & 7;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	if (!skb->dev)
		return NULL;

	if (pskb_trim_rcsum(skb, skb->len - 4))
		return NULL;

	return skb;
}