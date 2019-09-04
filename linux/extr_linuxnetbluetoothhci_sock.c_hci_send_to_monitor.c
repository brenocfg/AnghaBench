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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct hci_mon_hdr {void* len; void* index; void* opcode; } ;
struct hci_dev {int /*<<< orphan*/  id; } ;
typedef  void* __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  incoming; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_ACLDATA_PKT 132 
 int /*<<< orphan*/  HCI_CHANNEL_MONITOR ; 
#define  HCI_COMMAND_PKT 131 
#define  HCI_DIAG_PKT 130 
#define  HCI_EVENT_PKT 129 
 int /*<<< orphan*/  HCI_MON_ACL_RX_PKT ; 
 int /*<<< orphan*/  HCI_MON_ACL_TX_PKT ; 
 int /*<<< orphan*/  HCI_MON_COMMAND_PKT ; 
 int /*<<< orphan*/  HCI_MON_EVENT_PKT ; 
 int /*<<< orphan*/  HCI_MON_HDR_SIZE ; 
 int /*<<< orphan*/  HCI_MON_SCO_RX_PKT ; 
 int /*<<< orphan*/  HCI_MON_SCO_TX_PKT ; 
 int /*<<< orphan*/  HCI_MON_VENDOR_DIAG ; 
#define  HCI_SCODATA_PKT 128 
 int /*<<< orphan*/  HCI_SOCK_TRUSTED ; 
 struct sk_buff* __pskb_copy_fclone (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_to_channel (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  monitor_promisc ; 
 struct hci_mon_hdr* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 

void hci_send_to_monitor(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct sk_buff *skb_copy = NULL;
	struct hci_mon_hdr *hdr;
	__le16 opcode;

	if (!atomic_read(&monitor_promisc))
		return;

	BT_DBG("hdev %p len %d", hdev, skb->len);

	switch (hci_skb_pkt_type(skb)) {
	case HCI_COMMAND_PKT:
		opcode = cpu_to_le16(HCI_MON_COMMAND_PKT);
		break;
	case HCI_EVENT_PKT:
		opcode = cpu_to_le16(HCI_MON_EVENT_PKT);
		break;
	case HCI_ACLDATA_PKT:
		if (bt_cb(skb)->incoming)
			opcode = cpu_to_le16(HCI_MON_ACL_RX_PKT);
		else
			opcode = cpu_to_le16(HCI_MON_ACL_TX_PKT);
		break;
	case HCI_SCODATA_PKT:
		if (bt_cb(skb)->incoming)
			opcode = cpu_to_le16(HCI_MON_SCO_RX_PKT);
		else
			opcode = cpu_to_le16(HCI_MON_SCO_TX_PKT);
		break;
	case HCI_DIAG_PKT:
		opcode = cpu_to_le16(HCI_MON_VENDOR_DIAG);
		break;
	default:
		return;
	}

	/* Create a private copy with headroom */
	skb_copy = __pskb_copy_fclone(skb, HCI_MON_HDR_SIZE, GFP_ATOMIC, true);
	if (!skb_copy)
		return;

	/* Put header before the data */
	hdr = skb_push(skb_copy, HCI_MON_HDR_SIZE);
	hdr->opcode = opcode;
	hdr->index = cpu_to_le16(hdev->id);
	hdr->len = cpu_to_le16(skb->len);

	hci_send_to_channel(HCI_CHANNEL_MONITOR, skb_copy,
			    HCI_SOCK_TRUSTED, NULL);
	kfree_skb(skb_copy);
}