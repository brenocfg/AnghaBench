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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct nfc_dev {int dummy; } ;
struct nci_dev {int dummy; } ;
struct get_param_data {int /*<<< orphan*/  data; int /*<<< orphan*/  gate; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  HCI_GET_PARAM ; 
 int /*<<< orphan*/  NFC_ATTR_VENDOR_DATA ; 
 int /*<<< orphan*/  ST_NCI_VENDOR_OUI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nci_hci_get_param (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 struct sk_buff* nfc_vendor_cmd_alloc_reply_skb (struct nfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_vendor_cmd_reply (struct sk_buff*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_nci_hci_get_param(struct nfc_dev *dev, void *data,
				size_t data_len)
{
	int r;
	struct sk_buff *msg, *skb;
	struct nci_dev *ndev = nfc_get_drvdata(dev);
	struct get_param_data *param = (struct get_param_data *)data;

	if (data_len < sizeof(struct get_param_data))
		return -EPROTO;

	r = nci_hci_get_param(ndev, param->gate, param->data, &skb);
	if (r)
		goto exit;

	msg = nfc_vendor_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
					     HCI_GET_PARAM, skb->len);
	if (!msg) {
		r = -ENOMEM;
		goto free_skb;
	}

	if (nla_put(msg, NFC_ATTR_VENDOR_DATA, skb->len, skb->data)) {
		kfree_skb(msg);
		r = -ENOBUFS;
		goto free_skb;
	}

	r = nfc_vendor_cmd_reply(msg);

free_skb:
	kfree_skb(skb);
exit:
	return r;
}