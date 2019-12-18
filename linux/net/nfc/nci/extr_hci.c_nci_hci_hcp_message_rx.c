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
struct nci_dev {int dummy; } ;

/* Variables and functions */
#define  NCI_HCI_HCP_COMMAND 130 
#define  NCI_HCI_HCP_EVENT 129 
#define  NCI_HCI_HCP_RESPONSE 128 
 int /*<<< orphan*/  NCI_STATUS_OK ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_hci_cmd_received (struct nci_dev*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_hci_event_received (struct nci_dev*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_hci_resp_received (struct nci_dev*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static void nci_hci_hcp_message_rx(struct nci_dev *ndev, u8 pipe,
				   u8 type, u8 instruction, struct sk_buff *skb)
{
	switch (type) {
	case NCI_HCI_HCP_RESPONSE:
		nci_hci_resp_received(ndev, pipe, instruction, skb);
		break;
	case NCI_HCI_HCP_COMMAND:
		nci_hci_cmd_received(ndev, pipe, instruction, skb);
		break;
	case NCI_HCI_HCP_EVENT:
		nci_hci_event_received(ndev, pipe, instruction, skb);
		break;
	default:
		pr_err("UNKNOWN MSG Type %d, instruction=%d\n",
		       type, instruction);
		kfree_skb(skb);
		break;
	}

	nci_req_complete(ndev, NCI_STATUS_OK);
}