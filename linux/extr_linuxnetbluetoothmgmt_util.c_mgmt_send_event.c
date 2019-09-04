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
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct mgmt_hdr {void* len; void* index; void* opcode; } ;
struct hci_dev {scalar_t__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned short HCI_CHANNEL_CONTROL ; 
 scalar_t__ MGMT_INDEX_NONE ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  hci_send_monitor_ctrl_event (struct hci_dev*,scalar_t__,void*,scalar_t__,int /*<<< orphan*/ ,int,struct sock*) ; 
 int /*<<< orphan*/  hci_send_to_channel (unsigned short,struct sk_buff*,int,struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get_ktime (struct sk_buff*) ; 
 struct mgmt_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void*,scalar_t__) ; 

int mgmt_send_event(u16 event, struct hci_dev *hdev, unsigned short channel,
		    void *data, u16 data_len, int flag, struct sock *skip_sk)
{
	struct sk_buff *skb;
	struct mgmt_hdr *hdr;

	skb = alloc_skb(sizeof(*hdr) + data_len, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	hdr = skb_put(skb, sizeof(*hdr));
	hdr->opcode = cpu_to_le16(event);
	if (hdev)
		hdr->index = cpu_to_le16(hdev->id);
	else
		hdr->index = cpu_to_le16(MGMT_INDEX_NONE);
	hdr->len = cpu_to_le16(data_len);

	if (data)
		skb_put_data(skb, data, data_len);

	/* Time stamp */
	__net_timestamp(skb);

	hci_send_to_channel(channel, skb, flag, skip_sk);

	if (channel == HCI_CHANNEL_CONTROL)
		hci_send_monitor_ctrl_event(hdev, event, data, data_len,
					    skb_get_ktime(skb), flag, skip_sk);

	kfree_skb(skb);
	return 0;
}