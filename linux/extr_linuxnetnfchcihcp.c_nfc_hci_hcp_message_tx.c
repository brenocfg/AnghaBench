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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; } ;
struct nfc_hci_dev {int max_data_link_payload; int /*<<< orphan*/  msg_tx_work; int /*<<< orphan*/  msg_tx_mutex; int /*<<< orphan*/  msg_tx_queue; scalar_t__ shutting_down; struct nfc_dev* ndev; } ;
struct nfc_dev {int tx_headroom; int tx_tailroom; } ;
struct TYPE_2__ {struct TYPE_2__* data; int /*<<< orphan*/  header; } ;
struct hcp_packet {scalar_t__ header; TYPE_1__ message; } ;
struct hci_msg {int wait_response; unsigned long completion_delay; int /*<<< orphan*/  msg_frags; int /*<<< orphan*/  msg_l; void* cb_context; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  data_exchange_cb_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCP_HEADER (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NFC_HCI_FRAGMENT ; 
 scalar_t__ NFC_HCI_HCP_COMMAND ; 
 int NFC_HCI_HCP_PACKET_HEADER_LEN ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hci_msg*) ; 
 struct hci_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

int nfc_hci_hcp_message_tx(struct nfc_hci_dev *hdev, u8 pipe,
			   u8 type, u8 instruction,
			   const u8 *payload, size_t payload_len,
			   data_exchange_cb_t cb, void *cb_context,
			   unsigned long completion_delay)
{
	struct nfc_dev *ndev = hdev->ndev;
	struct hci_msg *cmd;
	const u8 *ptr = payload;
	int hci_len, err;
	bool firstfrag = true;

	cmd = kzalloc(sizeof(struct hci_msg), GFP_KERNEL);
	if (cmd == NULL)
		return -ENOMEM;

	INIT_LIST_HEAD(&cmd->msg_l);
	skb_queue_head_init(&cmd->msg_frags);
	cmd->wait_response = (type == NFC_HCI_HCP_COMMAND) ? true : false;
	cmd->cb = cb;
	cmd->cb_context = cb_context;
	cmd->completion_delay = completion_delay;

	hci_len = payload_len + 1;
	while (hci_len > 0) {
		struct sk_buff *skb;
		int skb_len, data_link_len;
		struct hcp_packet *packet;

		if (NFC_HCI_HCP_PACKET_HEADER_LEN + hci_len <=
		    hdev->max_data_link_payload)
			data_link_len = hci_len;
		else
			data_link_len = hdev->max_data_link_payload -
					NFC_HCI_HCP_PACKET_HEADER_LEN;

		skb_len = ndev->tx_headroom + NFC_HCI_HCP_PACKET_HEADER_LEN +
			  data_link_len + ndev->tx_tailroom;
		hci_len -= data_link_len;

		skb = alloc_skb(skb_len, GFP_KERNEL);
		if (skb == NULL) {
			err = -ENOMEM;
			goto out_skb_err;
		}
		skb_reserve(skb, ndev->tx_headroom);

		skb_put(skb, NFC_HCI_HCP_PACKET_HEADER_LEN + data_link_len);

		/* Only the last fragment will have the cb bit set to 1 */
		packet = (struct hcp_packet *)skb->data;
		packet->header = pipe;
		if (firstfrag) {
			firstfrag = false;
			packet->message.header = HCP_HEADER(type, instruction);
			if (ptr) {
				memcpy(packet->message.data, ptr,
				       data_link_len - 1);
				ptr += data_link_len - 1;
			}
		} else {
			memcpy(&packet->message, ptr, data_link_len);
			ptr += data_link_len;
		}

		/* This is the last fragment, set the cb bit */
		if (hci_len == 0)
			packet->header |= ~NFC_HCI_FRAGMENT;

		skb_queue_tail(&cmd->msg_frags, skb);
	}

	mutex_lock(&hdev->msg_tx_mutex);

	if (hdev->shutting_down) {
		err = -ESHUTDOWN;
		mutex_unlock(&hdev->msg_tx_mutex);
		goto out_skb_err;
	}

	list_add_tail(&cmd->msg_l, &hdev->msg_tx_queue);
	mutex_unlock(&hdev->msg_tx_mutex);

	schedule_work(&hdev->msg_tx_work);

	return 0;

out_skb_err:
	skb_queue_purge(&cmd->msg_frags);
	kfree(cmd);

	return err;
}