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
struct sk_buff {scalar_t__ cb; } ;
struct nfc_dev {int /*<<< orphan*/  cur_cmd_info; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

int nfc_vendor_cmd_reply(struct sk_buff *skb)
{
	struct nfc_dev *dev = ((void **)skb->cb)[0];
	void *hdr = ((void **)skb->cb)[1];

	/* clear CB data for netlink core to own from now on */
	memset(skb->cb, 0, sizeof(skb->cb));

	if (WARN_ON(!dev->cur_cmd_info)) {
		kfree_skb(skb);
		return -EINVAL;
	}

	genlmsg_end(skb, hdr);
	return genlmsg_reply(skb, dev->cur_cmd_info);
}