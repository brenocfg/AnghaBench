#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__* data; } ;
struct TYPE_5__ {scalar_t__ hci_muxed; } ;
struct nfcmrvl_private {TYPE_3__* ndev; int /*<<< orphan*/  flags; TYPE_2__ config; } ;
struct TYPE_6__ {TYPE_1__* nfc_dev; } ;
struct TYPE_4__ {scalar_t__ fw_download_in_progress; } ;

/* Variables and functions */
 scalar_t__ NFCMRVL_HCI_EVENT_CODE ; 
 int /*<<< orphan*/  NFCMRVL_HCI_EVENT_HEADER_SIZE ; 
 scalar_t__ NFCMRVL_HCI_NFC_EVENT_CODE ; 
 int /*<<< orphan*/  NFCMRVL_NCI_RUNNING ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_recv_frame (TYPE_3__*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfcmrvl_fw_dnld_recv_frame (struct nfcmrvl_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nfcmrvl_nci_recv_frame(struct nfcmrvl_private *priv, struct sk_buff *skb)
{
	if (priv->config.hci_muxed) {
		if (skb->data[0] == NFCMRVL_HCI_EVENT_CODE &&
		    skb->data[1] == NFCMRVL_HCI_NFC_EVENT_CODE) {
			/* Data packet, let's extract NCI payload */
			skb_pull(skb, NFCMRVL_HCI_EVENT_HEADER_SIZE);
		} else {
			/* Skip this packet */
			kfree_skb(skb);
			return 0;
		}
	}

	if (priv->ndev->nfc_dev->fw_download_in_progress) {
		nfcmrvl_fw_dnld_recv_frame(priv, skb);
		return 0;
	}

	if (test_bit(NFCMRVL_NCI_RUNNING, &priv->flags))
		nci_recv_frame(priv->ndev, skb);
	else {
		/* Drop this packet since nobody wants it */
		kfree_skb(skb);
		return 0;
	}

	return 0;
}