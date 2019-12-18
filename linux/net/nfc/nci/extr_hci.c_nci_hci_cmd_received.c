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
typedef  size_t u8 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct nci_hci_delete_pipe_noti {size_t pipe; } ;
struct nci_hci_create_pipe_resp {size_t dest_gate; size_t pipe; int /*<<< orphan*/  src_host; } ;
struct nci_hci_all_pipe_cleared_noti {int /*<<< orphan*/  host; } ;
struct nci_dev {TYPE_3__* ops; TYPE_2__* hci_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* hci_cmd_received ) (struct nci_dev*,size_t,size_t,struct sk_buff*) ;} ;
struct TYPE_5__ {size_t* gate2pipe; TYPE_1__* pipes; } ;
struct TYPE_4__ {size_t gate; int /*<<< orphan*/  host; } ;

/* Variables and functions */
#define  NCI_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED 131 
#define  NCI_HCI_ADM_NOTIFY_PIPE_CREATED 130 
#define  NCI_HCI_ADM_NOTIFY_PIPE_DELETED 129 
 size_t NCI_HCI_ANY_E_NOK ; 
 size_t NCI_HCI_ANY_OK ; 
#define  NCI_HCI_ANY_OPEN_PIPE 128 
 size_t NCI_HCI_FRAGMENT ; 
 size_t NCI_HCI_INVALID_GATE ; 
 int /*<<< orphan*/  NCI_HCI_INVALID_HOST ; 
 size_t NCI_HCI_MAX_PIPES ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nci_hci_reset_pipes_per_host (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_hci_send_data (struct nci_dev*,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,size_t,...) ; 
 int /*<<< orphan*/  stub1 (struct nci_dev*,size_t,size_t,struct sk_buff*) ; 

__attribute__((used)) static void nci_hci_cmd_received(struct nci_dev *ndev, u8 pipe,
				 u8 cmd, struct sk_buff *skb)
{
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 status = NCI_HCI_ANY_OK | ~NCI_HCI_FRAGMENT;
	u8 dest_gate, new_pipe;
	struct nci_hci_create_pipe_resp *create_info;
	struct nci_hci_delete_pipe_noti *delete_info;
	struct nci_hci_all_pipe_cleared_noti *cleared_info;

	pr_debug("from gate %x pipe %x cmd %x\n", gate, pipe, cmd);

	switch (cmd) {
	case NCI_HCI_ADM_NOTIFY_PIPE_CREATED:
		if (skb->len != 5) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}
		create_info = (struct nci_hci_create_pipe_resp *)skb->data;
		dest_gate = create_info->dest_gate;
		new_pipe = create_info->pipe;
		if (new_pipe >= NCI_HCI_MAX_PIPES) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}

		/* Save the new created pipe and bind with local gate,
		 * the description for skb->data[3] is destination gate id
		 * but since we received this cmd from host controller, we
		 * are the destination and it is our local gate
		 */
		ndev->hci_dev->gate2pipe[dest_gate] = new_pipe;
		ndev->hci_dev->pipes[new_pipe].gate = dest_gate;
		ndev->hci_dev->pipes[new_pipe].host =
						create_info->src_host;
		break;
	case NCI_HCI_ANY_OPEN_PIPE:
		/* If the pipe is not created report an error */
		if (gate == NCI_HCI_INVALID_GATE) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}
		break;
	case NCI_HCI_ADM_NOTIFY_PIPE_DELETED:
		if (skb->len != 1) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}
		delete_info = (struct nci_hci_delete_pipe_noti *)skb->data;
		if (delete_info->pipe >= NCI_HCI_MAX_PIPES) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}

		ndev->hci_dev->pipes[delete_info->pipe].gate =
						NCI_HCI_INVALID_GATE;
		ndev->hci_dev->pipes[delete_info->pipe].host =
						NCI_HCI_INVALID_HOST;
		break;
	case NCI_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED:
		if (skb->len != 1) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}

		cleared_info =
			(struct nci_hci_all_pipe_cleared_noti *)skb->data;
		nci_hci_reset_pipes_per_host(ndev, cleared_info->host);
		break;
	default:
		pr_debug("Discarded unknown cmd %x to gate %x\n", cmd, gate);
		break;
	}

	if (ndev->ops->hci_cmd_received)
		ndev->ops->hci_cmd_received(ndev, pipe, cmd, skb);

exit:
	nci_hci_send_data(ndev, pipe, status, NULL, 0);

	kfree_skb(skb);
}