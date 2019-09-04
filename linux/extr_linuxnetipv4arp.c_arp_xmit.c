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
struct sk_buff {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_ARP ; 
 int /*<<< orphan*/  NF_ARP_OUT ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_xmit_finish ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 

void arp_xmit(struct sk_buff *skb)
{
	/* Send it off, maybe filter it using firewalling first.  */
	NF_HOOK(NFPROTO_ARP, NF_ARP_OUT,
		dev_net(skb->dev), NULL, skb, NULL, skb->dev,
		arp_xmit_finish);
}