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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_cmd_status {scalar_t__ status; scalar_t__ ncmd; int /*<<< orphan*/  opcode; } ;
struct hci_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_cnt; scalar_t__ sent_cmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_timer; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  hci_req_complete_t ;
typedef  int /*<<< orphan*/  hci_req_complete_skb_t ;
struct TYPE_3__ {int /*<<< orphan*/  req_event; } ;
struct TYPE_4__ {TYPE_1__ hci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CMD_PENDING ; 
#define  HCI_OP_ADD_SCO 144 
#define  HCI_OP_AUTH_REQUESTED 143 
#define  HCI_OP_CREATE_CONN 142 
#define  HCI_OP_DISCONNECT 141 
#define  HCI_OP_EXIT_SNIFF_MODE 140 
#define  HCI_OP_INQUIRY 139 
#define  HCI_OP_LE_CREATE_CONN 138 
#define  HCI_OP_LE_EXT_CREATE_CONN 137 
#define  HCI_OP_LE_READ_REMOTE_FEATURES 136 
#define  HCI_OP_LE_START_ENC 135 
 int /*<<< orphan*/  HCI_OP_NOP ; 
#define  HCI_OP_READ_REMOTE_EXT_FEATURES 134 
#define  HCI_OP_READ_REMOTE_FEATURES 133 
#define  HCI_OP_REMOTE_NAME_REQ 132 
#define  HCI_OP_SETUP_SYNC_CONN 131 
#define  HCI_OP_SET_CONN_ENCRYPT 130 
#define  HCI_OP_SNIFF_MODE 129 
#define  HCI_OP_SWITCH_ROLE 128 
 int /*<<< orphan*/  HCI_RESET ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* bt_cb (scalar_t__) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_cs_add_sco (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_auth_requested (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_create_conn (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_disconnect (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_exit_sniff_mode (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_inquiry (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_le_create_conn (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_le_ext_create_conn (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_le_read_remote_features (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_le_start_enc (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_read_remote_ext_features (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_read_remote_features (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_remote_name_req (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_set_conn_encrypt (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_setup_sync_conn (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_sniff_mode (struct hci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  hci_cs_switch_role (struct hci_dev*,scalar_t__) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_cmd_complete (struct hci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_cmd_status_evt(struct hci_dev *hdev, struct sk_buff *skb,
			       u16 *opcode, u8 *status,
			       hci_req_complete_t *req_complete,
			       hci_req_complete_skb_t *req_complete_skb)
{
	struct hci_ev_cmd_status *ev = (void *) skb->data;

	skb_pull(skb, sizeof(*ev));

	*opcode = __le16_to_cpu(ev->opcode);
	*status = ev->status;

	switch (*opcode) {
	case HCI_OP_INQUIRY:
		hci_cs_inquiry(hdev, ev->status);
		break;

	case HCI_OP_CREATE_CONN:
		hci_cs_create_conn(hdev, ev->status);
		break;

	case HCI_OP_DISCONNECT:
		hci_cs_disconnect(hdev, ev->status);
		break;

	case HCI_OP_ADD_SCO:
		hci_cs_add_sco(hdev, ev->status);
		break;

	case HCI_OP_AUTH_REQUESTED:
		hci_cs_auth_requested(hdev, ev->status);
		break;

	case HCI_OP_SET_CONN_ENCRYPT:
		hci_cs_set_conn_encrypt(hdev, ev->status);
		break;

	case HCI_OP_REMOTE_NAME_REQ:
		hci_cs_remote_name_req(hdev, ev->status);
		break;

	case HCI_OP_READ_REMOTE_FEATURES:
		hci_cs_read_remote_features(hdev, ev->status);
		break;

	case HCI_OP_READ_REMOTE_EXT_FEATURES:
		hci_cs_read_remote_ext_features(hdev, ev->status);
		break;

	case HCI_OP_SETUP_SYNC_CONN:
		hci_cs_setup_sync_conn(hdev, ev->status);
		break;

	case HCI_OP_SNIFF_MODE:
		hci_cs_sniff_mode(hdev, ev->status);
		break;

	case HCI_OP_EXIT_SNIFF_MODE:
		hci_cs_exit_sniff_mode(hdev, ev->status);
		break;

	case HCI_OP_SWITCH_ROLE:
		hci_cs_switch_role(hdev, ev->status);
		break;

	case HCI_OP_LE_CREATE_CONN:
		hci_cs_le_create_conn(hdev, ev->status);
		break;

	case HCI_OP_LE_READ_REMOTE_FEATURES:
		hci_cs_le_read_remote_features(hdev, ev->status);
		break;

	case HCI_OP_LE_START_ENC:
		hci_cs_le_start_enc(hdev, ev->status);
		break;

	case HCI_OP_LE_EXT_CREATE_CONN:
		hci_cs_le_ext_create_conn(hdev, ev->status);
		break;

	default:
		BT_DBG("%s opcode 0x%4.4x", hdev->name, *opcode);
		break;
	}

	if (*opcode != HCI_OP_NOP)
		cancel_delayed_work(&hdev->cmd_timer);

	if (ev->ncmd && !test_bit(HCI_RESET, &hdev->flags))
		atomic_set(&hdev->cmd_cnt, 1);

	/* Indicate request completion if the command failed. Also, if
	 * we're not waiting for a special event and we get a success
	 * command status we should try to flag the request as completed
	 * (since for this kind of commands there will not be a command
	 * complete event).
	 */
	if (ev->status ||
	    (hdev->sent_cmd && !bt_cb(hdev->sent_cmd)->hci.req_event))
		hci_req_cmd_complete(hdev, *opcode, ev->status, req_complete,
				     req_complete_skb);

	if (hci_dev_test_flag(hdev, HCI_CMD_PENDING)) {
		bt_dev_err(hdev,
			   "unexpected event for opcode 0x%4.4x", *opcode);
		return;
	}

	if (atomic_read(&hdev->cmd_cnt) && !skb_queue_empty(&hdev->cmd_q))
		queue_work(hdev->workqueue, &hdev->cmd_work);
}