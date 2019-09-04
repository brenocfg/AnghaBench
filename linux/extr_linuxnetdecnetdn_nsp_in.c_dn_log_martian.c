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
struct sk_buff {TYPE_1__* dev; } ;
struct dn_skb_cb {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 scalar_t__ decnet_log_martians ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dn_log_martian(struct sk_buff *skb, const char *msg)
{
	if (decnet_log_martians) {
		char *devname = skb->dev ? skb->dev->name : "???";
		struct dn_skb_cb *cb = DN_SKB_CB(skb);
		net_info_ratelimited("DECnet: Martian packet (%s) dev=%s src=0x%04hx dst=0x%04hx srcport=0x%04hx dstport=0x%04hx\n",
				     msg, devname,
				     le16_to_cpu(cb->src),
				     le16_to_cpu(cb->dst),
				     le16_to_cpu(cb->src_port),
				     le16_to_cpu(cb->dst_port));
	}
}