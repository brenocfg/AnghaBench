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
struct sk_buff {int dummy; } ;
struct qrtr_tun {int /*<<< orphan*/  queue; int /*<<< orphan*/  ep; } ;
struct inode {int dummy; } ;
struct file {struct qrtr_tun* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qrtr_tun*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  qrtr_endpoint_unregister (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qrtr_tun_release(struct inode *inode, struct file *filp)
{
	struct qrtr_tun *tun = filp->private_data;
	struct sk_buff *skb;

	qrtr_endpoint_unregister(&tun->ep);

	/* Discard all SKBs */
	while (!skb_queue_empty(&tun->queue)) {
		skb = skb_dequeue(&tun->queue);
		kfree_skb(skb);
	}

	kfree(tun);

	return 0;
}