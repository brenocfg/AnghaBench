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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct hci_mon_hdr {void* len; void* index; void* opcode; } ;
struct TYPE_4__ {int channel; TYPE_1__* hdev; int /*<<< orphan*/  cookie; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_CHANNEL_CONTROL 130 
#define  HCI_CHANNEL_RAW 129 
#define  HCI_CHANNEL_USER 128 
 scalar_t__ HCI_DEV_NONE ; 
 scalar_t__ HCI_MON_CTRL_CLOSE ; 
 scalar_t__ HCI_MON_HDR_SIZE ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 TYPE_2__* hci_pi (struct sock*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hci_mon_hdr* skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *create_monitor_ctrl_close(struct sock *sk)
{
	struct hci_mon_hdr *hdr;
	struct sk_buff *skb;

	/* No message needed when cookie is not present */
	if (!hci_pi(sk)->cookie)
		return NULL;

	switch (hci_pi(sk)->channel) {
	case HCI_CHANNEL_RAW:
	case HCI_CHANNEL_USER:
	case HCI_CHANNEL_CONTROL:
		break;
	default:
		/* No message for unsupported format */
		return NULL;
	}

	skb = bt_skb_alloc(4, GFP_ATOMIC);
	if (!skb)
		return NULL;

	put_unaligned_le32(hci_pi(sk)->cookie, skb_put(skb, 4));

	__net_timestamp(skb);

	hdr = skb_push(skb, HCI_MON_HDR_SIZE);
	hdr->opcode = cpu_to_le16(HCI_MON_CTRL_CLOSE);
	if (hci_pi(sk)->hdev)
		hdr->index = cpu_to_le16(hci_pi(sk)->hdev->id);
	else
		hdr->index = cpu_to_le16(HCI_DEV_NONE);
	hdr->len = cpu_to_le16(skb->len - HCI_MON_HDR_SIZE);

	return skb;
}