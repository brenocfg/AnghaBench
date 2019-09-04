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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
#define  NFC_HCI_HCP_COMMAND 130 
#define  NFC_HCI_HCP_EVENT 129 
#define  NFC_HCI_HCP_RESPONSE 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_hci_cmd_received (struct nfc_hci_dev*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_hci_event_received (struct nfc_hci_dev*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_hci_resp_received (struct nfc_hci_dev*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

void nfc_hci_hcp_message_rx(struct nfc_hci_dev *hdev, u8 pipe, u8 type,
			    u8 instruction, struct sk_buff *skb)
{
	switch (type) {
	case NFC_HCI_HCP_RESPONSE:
		nfc_hci_resp_received(hdev, instruction, skb);
		break;
	case NFC_HCI_HCP_COMMAND:
		nfc_hci_cmd_received(hdev, pipe, instruction, skb);
		break;
	case NFC_HCI_HCP_EVENT:
		nfc_hci_event_received(hdev, pipe, instruction, skb);
		break;
	default:
		pr_err("UNKNOWN MSG Type %d, instruction=%d\n",
		       type, instruction);
		kfree_skb(skb);
		break;
	}
}