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
typedef  size_t u8 ;
struct sk_buff {size_t* data; int len; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; TYPE_1__* pipes; } ;
struct TYPE_2__ {size_t gate; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int /*<<< orphan*/  NFC_COMM_PASSIVE ; 
 int /*<<< orphan*/  NFC_HCI_EVT_END_OPERATION ; 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP_MASK ; 
 int /*<<< orphan*/  PN544_DEP_ATR_REQ ; 
#define  PN544_HCI_EVT_ACTIVATED 130 
#define  PN544_HCI_EVT_DEACTIVATED 129 
#define  PN544_HCI_EVT_RCV_DATA 128 
 size_t PN544_RF_READER_NFCIP1_INITIATOR_GATE ; 
 size_t PN544_RF_READER_NFCIP1_TARGET_GATE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,size_t,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int nfc_hci_send_event (struct nfc_hci_dev*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfc_hci_target_discovered (struct nfc_hci_dev*,size_t) ; 
 int nfc_tm_activated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int nfc_tm_data_received (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int pn544_hci_event_received(struct nfc_hci_dev *hdev, u8 pipe, u8 event,
				    struct sk_buff *skb)
{
	struct sk_buff *rgb_skb = NULL;
	u8 gate = hdev->pipes[pipe].gate;
	int r;

	pr_debug("hci event %d\n", event);
	switch (event) {
	case PN544_HCI_EVT_ACTIVATED:
		if (gate == PN544_RF_READER_NFCIP1_INITIATOR_GATE) {
			r = nfc_hci_target_discovered(hdev, gate);
		} else if (gate == PN544_RF_READER_NFCIP1_TARGET_GATE) {
			r = nfc_hci_get_param(hdev, gate, PN544_DEP_ATR_REQ,
					      &rgb_skb);
			if (r < 0)
				goto exit;

			r = nfc_tm_activated(hdev->ndev, NFC_PROTO_NFC_DEP_MASK,
					     NFC_COMM_PASSIVE, rgb_skb->data,
					     rgb_skb->len);

			kfree_skb(rgb_skb);
		} else {
			r = -EINVAL;
		}
		break;
	case PN544_HCI_EVT_DEACTIVATED:
		r = nfc_hci_send_event(hdev, gate, NFC_HCI_EVT_END_OPERATION,
				       NULL, 0);
		break;
	case PN544_HCI_EVT_RCV_DATA:
		if (skb->len < 2) {
			r = -EPROTO;
			goto exit;
		}

		if (skb->data[0] != 0) {
			pr_debug("data0 %d\n", skb->data[0]);
			r = -EPROTO;
			goto exit;
		}

		skb_pull(skb, 2);
		return nfc_tm_data_received(hdev->ndev, skb);
	default:
		return 1;
	}

exit:
	kfree_skb(skb);

	return r;
}