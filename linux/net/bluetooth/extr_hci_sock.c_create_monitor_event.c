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
struct sk_buff {int len; } ;
struct hci_mon_new_index {int /*<<< orphan*/  name; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  bus; int /*<<< orphan*/  type; } ;
struct hci_mon_index_info {void* manufacturer; int /*<<< orphan*/  bdaddr; } ;
struct hci_mon_hdr {void* len; void* index; void* opcode; } ;
struct hci_dev {int manufacturer; int id; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  name; int /*<<< orphan*/  bus; int /*<<< orphan*/  dev_type; } ;
typedef  void* __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_DEV_CLOSE 133 
#define  HCI_DEV_OPEN 132 
#define  HCI_DEV_REG 131 
#define  HCI_DEV_SETUP 130 
#define  HCI_DEV_UNREG 129 
#define  HCI_DEV_UP 128 
 int HCI_MON_CLOSE_INDEX ; 
 int HCI_MON_DEL_INDEX ; 
 int HCI_MON_HDR_SIZE ; 
 int HCI_MON_INDEX_INFO ; 
 int /*<<< orphan*/  HCI_MON_INDEX_INFO_SIZE ; 
 int HCI_MON_NEW_INDEX ; 
 int /*<<< orphan*/  HCI_MON_NEW_INDEX_SIZE ; 
 int HCI_MON_OPEN_INDEX ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sk_buff* bt_skb_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hci_mon_hdr* skb_push (struct sk_buff*,int) ; 
 void* skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *create_monitor_event(struct hci_dev *hdev, int event)
{
	struct hci_mon_hdr *hdr;
	struct hci_mon_new_index *ni;
	struct hci_mon_index_info *ii;
	struct sk_buff *skb;
	__le16 opcode;

	switch (event) {
	case HCI_DEV_REG:
		skb = bt_skb_alloc(HCI_MON_NEW_INDEX_SIZE, GFP_ATOMIC);
		if (!skb)
			return NULL;

		ni = skb_put(skb, HCI_MON_NEW_INDEX_SIZE);
		ni->type = hdev->dev_type;
		ni->bus = hdev->bus;
		bacpy(&ni->bdaddr, &hdev->bdaddr);
		memcpy(ni->name, hdev->name, 8);

		opcode = cpu_to_le16(HCI_MON_NEW_INDEX);
		break;

	case HCI_DEV_UNREG:
		skb = bt_skb_alloc(0, GFP_ATOMIC);
		if (!skb)
			return NULL;

		opcode = cpu_to_le16(HCI_MON_DEL_INDEX);
		break;

	case HCI_DEV_SETUP:
		if (hdev->manufacturer == 0xffff)
			return NULL;

		/* fall through */

	case HCI_DEV_UP:
		skb = bt_skb_alloc(HCI_MON_INDEX_INFO_SIZE, GFP_ATOMIC);
		if (!skb)
			return NULL;

		ii = skb_put(skb, HCI_MON_INDEX_INFO_SIZE);
		bacpy(&ii->bdaddr, &hdev->bdaddr);
		ii->manufacturer = cpu_to_le16(hdev->manufacturer);

		opcode = cpu_to_le16(HCI_MON_INDEX_INFO);
		break;

	case HCI_DEV_OPEN:
		skb = bt_skb_alloc(0, GFP_ATOMIC);
		if (!skb)
			return NULL;

		opcode = cpu_to_le16(HCI_MON_OPEN_INDEX);
		break;

	case HCI_DEV_CLOSE:
		skb = bt_skb_alloc(0, GFP_ATOMIC);
		if (!skb)
			return NULL;

		opcode = cpu_to_le16(HCI_MON_CLOSE_INDEX);
		break;

	default:
		return NULL;
	}

	__net_timestamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = opcode;
	hdr->index = cpu_to_le16(hdev->id);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	return skb;
}