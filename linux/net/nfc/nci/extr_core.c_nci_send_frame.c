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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nci_dev {TYPE_1__* ops; int /*<<< orphan*/  nfc_dev; } ;
struct TYPE_2__ {int (* send ) (struct nci_dev*,struct sk_buff*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NFC_DIRECTION_TX ; 
 int /*<<< orphan*/  RAW_PAYLOAD_NCI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_send_to_raw_sock (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int stub1 (struct nci_dev*,struct sk_buff*) ; 

int nci_send_frame(struct nci_dev *ndev, struct sk_buff *skb)
{
	pr_debug("len %d\n", skb->len);

	if (!ndev) {
		kfree_skb(skb);
		return -ENODEV;
	}

	/* Get rid of skb owner, prior to sending to the driver. */
	skb_orphan(skb);

	/* Send copy to sniffer */
	nfc_send_to_raw_sock(ndev->nfc_dev, skb,
			     RAW_PAYLOAD_NCI, NFC_DIRECTION_TX);

	return ndev->ops->send(ndev, skb);
}