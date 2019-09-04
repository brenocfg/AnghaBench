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
typedef  int /*<<< orphan*/  ver ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct hci_mon_hdr {void* len; void* index; void* opcode; } ;
struct TYPE_4__ {int cookie; int channel; TYPE_1__* hdev; int /*<<< orphan*/ * comm; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int BT_SUBSYS_REVISION ; 
 int /*<<< orphan*/  BT_SUBSYS_VERSION ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_CHANNEL_CONTROL 130 
#define  HCI_CHANNEL_RAW 129 
#define  HCI_CHANNEL_USER 128 
 scalar_t__ HCI_DEV_NONE ; 
 scalar_t__ HCI_MON_CTRL_OPEN ; 
 scalar_t__ HCI_MON_HDR_SIZE ; 
 int /*<<< orphan*/  HCI_SOCK_TRUSTED ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 TYPE_2__* hci_pi (struct sock*) ; 
 scalar_t__ hci_sock_test_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_fill_version_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 struct hci_mon_hdr* skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *create_monitor_ctrl_open(struct sock *sk)
{
	struct hci_mon_hdr *hdr;
	struct sk_buff *skb;
	u16 format;
	u8 ver[3];
	u32 flags;

	/* No message needed when cookie is not present */
	if (!hci_pi(sk)->cookie)
		return NULL;

	switch (hci_pi(sk)->channel) {
	case HCI_CHANNEL_RAW:
		format = 0x0000;
		ver[0] = BT_SUBSYS_VERSION;
		put_unaligned_le16(BT_SUBSYS_REVISION, ver + 1);
		break;
	case HCI_CHANNEL_USER:
		format = 0x0001;
		ver[0] = BT_SUBSYS_VERSION;
		put_unaligned_le16(BT_SUBSYS_REVISION, ver + 1);
		break;
	case HCI_CHANNEL_CONTROL:
		format = 0x0002;
		mgmt_fill_version_info(ver);
		break;
	default:
		/* No message for unsupported format */
		return NULL;
	}

	skb = bt_skb_alloc(14 + TASK_COMM_LEN , GFP_ATOMIC);
	if (!skb)
		return NULL;

	flags = hci_sock_test_flag(sk, HCI_SOCK_TRUSTED) ? 0x1 : 0x0;

	put_unaligned_le32(hci_pi(sk)->cookie, skb_put(skb, 4));
	put_unaligned_le16(format, skb_put(skb, 2));
	skb_put_data(skb, ver, sizeof(ver));
	put_unaligned_le32(flags, skb_put(skb, 4));
	skb_put_u8(skb, TASK_COMM_LEN);
	skb_put_data(skb, hci_pi(sk)->comm, TASK_COMM_LEN);

	__net_timestamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_CTRL_OPEN);
	if (hci_pi(sk)->hdev)
		hdr->index = cpu_to_le16(hci_pi(sk)->hdev->id);
	else
		hdr->index = cpu_to_le16(HCI_DEV_NONE);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	return skb;
}