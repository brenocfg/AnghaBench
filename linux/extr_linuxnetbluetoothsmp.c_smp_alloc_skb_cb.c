#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct l2cap_chan {int dummy; } ;
struct TYPE_3__ {struct l2cap_chan* chan; } ;
struct TYPE_4__ {TYPE_1__ l2cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_PRIO_MAX ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *smp_alloc_skb_cb(struct l2cap_chan *chan,
					unsigned long hdr_len,
					unsigned long len, int nb)
{
	struct sk_buff *skb;

	skb = bt_skb_alloc(hdr_len + len, GFP_KERNEL);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	skb->priority = HCI_PRIO_MAX;
	bt_cb(skb)->l2cap.chan = chan;

	return skb;
}