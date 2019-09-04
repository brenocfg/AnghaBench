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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rfcomm_dev {int /*<<< orphan*/  port; int /*<<< orphan*/  dlc; int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ tty_insert_flip_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_tty_copy_pending(struct rfcomm_dev *dev)
{
	struct sk_buff *skb;
	int inserted = 0;

	BT_DBG("dev %p", dev);

	rfcomm_dlc_lock(dev->dlc);

	while ((skb = skb_dequeue(&dev->pending))) {
		inserted += tty_insert_flip_string(&dev->port, skb->data,
				skb->len);
		kfree_skb(skb);
	}

	rfcomm_dlc_unlock(dev->dlc);

	if (inserted > 0)
		tty_flip_buffer_push(&dev->port);
}