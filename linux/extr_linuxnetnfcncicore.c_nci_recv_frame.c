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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nci_dev {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_wq; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NCI_INIT ; 
 int /*<<< orphan*/  NCI_UP ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nci_recv_frame(struct nci_dev *ndev, struct sk_buff *skb)
{
	pr_debug("len %d\n", skb->len);

	if (!ndev || (!test_bit(NCI_UP, &ndev->flags) &&
	    !test_bit(NCI_INIT, &ndev->flags))) {
		kfree_skb(skb);
		return -ENXIO;
	}

	/* Queue frame for rx worker thread */
	skb_queue_tail(&ndev->rx_q, skb);
	queue_work(ndev->rx_wq, &ndev->rx_work);

	return 0;
}