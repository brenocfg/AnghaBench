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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct canfd_frame {int dummy; } ;
struct can_skb_priv {int dummy; } ;
struct bcm_op {int cfsiz; int currframe; int nframes; int /*<<< orphan*/  frames_abs; int /*<<< orphan*/  sk; int /*<<< orphan*/  ifindex; struct canfd_frame* frames; } ;
struct TYPE_2__ {scalar_t__ skbcnt; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_send (struct sk_buff*,int) ; 
 TYPE_1__* can_skb_prv (struct sk_buff*) ; 
 int /*<<< orphan*/  can_skb_reserve (struct sk_buff*) ; 
 int /*<<< orphan*/  can_skb_set_owner (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct canfd_frame*,int) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_can_tx(struct bcm_op *op)
{
	struct sk_buff *skb;
	struct net_device *dev;
	struct canfd_frame *cf = op->frames + op->cfsiz * op->currframe;

	/* no target device? => exit */
	if (!op->ifindex)
		return;

	dev = dev_get_by_index(sock_net(op->sk), op->ifindex);
	if (!dev) {
		/* RFC: should this bcm_op remove itself here? */
		return;
	}

	skb = alloc_skb(op->cfsiz + sizeof(struct can_skb_priv), gfp_any());
	if (!skb)
		goto out;

	can_skb_reserve(skb);
	can_skb_prv(skb)->ifindex = dev->ifindex;
	can_skb_prv(skb)->skbcnt = 0;

	skb_put_data(skb, cf, op->cfsiz);

	/* send with loopback */
	skb->dev = dev;
	can_skb_set_owner(skb, op->sk);
	can_send(skb, 1);

	/* update statistics */
	op->currframe++;
	op->frames_abs++;

	/* reached last frame? */
	if (op->currframe >= op->nframes)
		op->currframe = 0;
out:
	dev_put(dev);
}