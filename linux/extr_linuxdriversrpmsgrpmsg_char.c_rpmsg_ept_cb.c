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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rpmsg_eptdev {int /*<<< orphan*/  readq; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; } ;
struct rpmsg_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpmsg_ept_cb(struct rpmsg_device *rpdev, void *buf, int len,
			void *priv, u32 addr)
{
	struct rpmsg_eptdev *eptdev = priv;
	struct sk_buff *skb;

	skb = alloc_skb(len, GFP_ATOMIC);
	if (!skb)
		return -ENOMEM;

	skb_put_data(skb, buf, len);

	spin_lock(&eptdev->queue_lock);
	skb_queue_tail(&eptdev->queue, skb);
	spin_unlock(&eptdev->queue_lock);

	/* wake up any blocking processes, waiting for new data */
	wake_up_interruptible(&eptdev->readq);

	return 0;
}