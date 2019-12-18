#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct nfc_hci_dev {size_t* gate2pipe; TYPE_2__* ops; TYPE_1__* pipes; } ;
struct hci_delete_pipe_noti {size_t pipe; } ;
struct hci_create_pipe_resp {size_t pipe; size_t dest_gate; int /*<<< orphan*/  src_host; } ;
struct hci_all_pipe_cleared_noti {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cmd_received ) (struct nfc_hci_dev*,size_t,size_t,struct sk_buff*) ;} ;
struct TYPE_3__ {size_t gate; int /*<<< orphan*/  dest_host; } ;

/* Variables and functions */
#define  NFC_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED 131 
#define  NFC_HCI_ADM_NOTIFY_PIPE_CREATED 130 
#define  NFC_HCI_ADM_NOTIFY_PIPE_DELETED 129 
 size_t NFC_HCI_ANY_E_NOK ; 
 size_t NFC_HCI_ANY_OK ; 
#define  NFC_HCI_ANY_OPEN_PIPE 128 
 int /*<<< orphan*/  NFC_HCI_HCP_RESPONSE ; 
 size_t NFC_HCI_INVALID_GATE ; 
 int /*<<< orphan*/  NFC_HCI_INVALID_HOST ; 
 size_t NFC_HCI_MAX_PIPES ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_hci_hcp_message_tx (struct nfc_hci_dev*,size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_hci_reset_pipes_per_host (struct nfc_hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (struct nfc_hci_dev*,size_t,size_t,struct sk_buff*) ; 

void nfc_hci_cmd_received(struct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			  struct sk_buff *skb)
{
	u8 gate = hdev->pipes[pipe].gate;
	u8 status = NFC_HCI_ANY_OK;
	struct hci_create_pipe_resp *create_info;
	struct hci_delete_pipe_noti *delete_info;
	struct hci_all_pipe_cleared_noti *cleared_info;

	pr_debug("from gate %x pipe %x cmd %x\n", gate, pipe, cmd);

	switch (cmd) {
	case NFC_HCI_ADM_NOTIFY_PIPE_CREATED:
		if (skb->len != 5) {
			status = NFC_HCI_ANY_E_NOK;
			goto exit;
		}
		create_info = (struct hci_create_pipe_resp *)skb->data;

		if (create_info->pipe >= NFC_HCI_MAX_PIPES) {
			status = NFC_HCI_ANY_E_NOK;
			goto exit;
		}

		/* Save the new created pipe and bind with local gate,
		 * the description for skb->data[3] is destination gate id
		 * but since we received this cmd from host controller, we
		 * are the destination and it is our local gate
		 */
		hdev->gate2pipe[create_info->dest_gate] = create_info->pipe;
		hdev->pipes[create_info->pipe].gate = create_info->dest_gate;
		hdev->pipes[create_info->pipe].dest_host =
							create_info->src_host;
		break;
	case NFC_HCI_ANY_OPEN_PIPE:
		if (gate == NFC_HCI_INVALID_GATE) {
			status = NFC_HCI_ANY_E_NOK;
			goto exit;
		}
		break;
	case NFC_HCI_ADM_NOTIFY_PIPE_DELETED:
		if (skb->len != 1) {
			status = NFC_HCI_ANY_E_NOK;
			goto exit;
		}
		delete_info = (struct hci_delete_pipe_noti *)skb->data;

		if (delete_info->pipe >= NFC_HCI_MAX_PIPES) {
			status = NFC_HCI_ANY_E_NOK;
			goto exit;
		}

		hdev->pipes[delete_info->pipe].gate = NFC_HCI_INVALID_GATE;
		hdev->pipes[delete_info->pipe].dest_host = NFC_HCI_INVALID_HOST;
		break;
	case NFC_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED:
		if (skb->len != 1) {
			status = NFC_HCI_ANY_E_NOK;
			goto exit;
		}
		cleared_info = (struct hci_all_pipe_cleared_noti *)skb->data;

		nfc_hci_reset_pipes_per_host(hdev, cleared_info->host);
		break;
	default:
		pr_info("Discarded unknown cmd %x to gate %x\n", cmd, gate);
		break;
	}

	if (hdev->ops->cmd_received)
		hdev->ops->cmd_received(hdev, pipe, cmd, skb);

exit:
	nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_RESPONSE,
			       status, NULL, 0, NULL, NULL, 0);

	kfree_skb(skb);
}