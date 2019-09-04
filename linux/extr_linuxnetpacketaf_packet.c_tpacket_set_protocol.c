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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void tpacket_set_protocol(const struct net_device *dev,
				 struct sk_buff *skb)
{
	if (dev->type == ARPHRD_ETHER) {
		skb_reset_mac_header(skb);
		skb->protocol = eth_hdr(skb)->h_proto;
	}
}