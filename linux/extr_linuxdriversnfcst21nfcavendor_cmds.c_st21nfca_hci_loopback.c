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
struct TYPE_2__ {struct sk_buff* rx_skb; int /*<<< orphan*/  req_completion; } ;
struct st21nfca_hci_info {TYPE_1__ vendor_info; } ;
struct sk_buff {size_t len; int /*<<< orphan*/  data; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; } ;
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  HCI_LOOPBACK ; 
 int /*<<< orphan*/  NFC_ATTR_VENDOR_DATA ; 
 int /*<<< orphan*/  NFC_HCI_LOOPBACK_GATE ; 
 int /*<<< orphan*/  ST21NFCA_EVT_POST_DATA ; 
 int /*<<< orphan*/  ST21NFCA_VENDOR_OUI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 struct sk_buff* nfc_vendor_cmd_alloc_reply_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int nfc_vendor_cmd_reply (struct sk_buff*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st21nfca_hci_loopback(struct nfc_dev *dev, void *data,
				 size_t data_len)
{
	int r;
	struct sk_buff *msg;
	struct nfc_hci_dev *hdev = nfc_get_drvdata(dev);
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	if (data_len <= 0)
		return -EPROTO;

	reinit_completion(&info->vendor_info.req_completion);
	info->vendor_info.rx_skb = NULL;

	r = nfc_hci_send_event(hdev, NFC_HCI_LOOPBACK_GATE,
			       ST21NFCA_EVT_POST_DATA, data, data_len);
	if (r < 0) {
		r = -EPROTO;
		goto exit;
	}

	wait_for_completion_interruptible(&info->vendor_info.req_completion);
	if (!info->vendor_info.rx_skb ||
	    info->vendor_info.rx_skb->len != data_len) {
		r = -EPROTO;
		goto exit;
	}

	msg = nfc_vendor_cmd_alloc_reply_skb(hdev->ndev,
					ST21NFCA_VENDOR_OUI,
					HCI_LOOPBACK,
					info->vendor_info.rx_skb->len);
	if (!msg) {
		r = -ENOMEM;
		goto free_skb;
	}

	if (nla_put(msg, NFC_ATTR_VENDOR_DATA, info->vendor_info.rx_skb->len,
		    info->vendor_info.rx_skb->data)) {
		kfree_skb(msg);
		r = -ENOBUFS;
		goto free_skb;
	}

	r = nfc_vendor_cmd_reply(msg);
free_skb:
	kfree_skb(info->vendor_info.rx_skb);
exit:
	return r;
}