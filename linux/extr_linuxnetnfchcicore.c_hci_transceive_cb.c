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
struct nfc_hci_dev {int async_cb_type; int /*<<< orphan*/  async_cb_context; int /*<<< orphan*/  (* async_cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;

/* Variables and functions */
#define  HCI_CB_TYPE_TRANSCEIVE 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void hci_transceive_cb(void *context, struct sk_buff *skb, int err)
{
	struct nfc_hci_dev *hdev = context;

	switch (hdev->async_cb_type) {
	case HCI_CB_TYPE_TRANSCEIVE:
		/*
		 * TODO: Check RF Error indicator to make sure data is valid.
		 * It seems that HCI cmd can complete without error, but data
		 * can be invalid if an RF error occured? Ignore for now.
		 */
		if (err == 0)
			skb_trim(skb, skb->len - 1); /* RF Err ind */

		hdev->async_cb(hdev->async_cb_context, skb, err);
		break;
	default:
		if (err == 0)
			kfree_skb(skb);
		break;
	}
}