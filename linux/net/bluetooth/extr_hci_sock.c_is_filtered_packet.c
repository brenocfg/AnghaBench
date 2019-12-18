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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct hci_filter {scalar_t__ opcode; int /*<<< orphan*/  event_mask; int /*<<< orphan*/  type_mask; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {struct hci_filter filter; } ;

/* Variables and functions */
 int HCI_EVENT_PKT ; 
 int HCI_EV_CMD_COMPLETE ; 
 int HCI_EV_CMD_STATUS ; 
 int HCI_FLT_EVENT_BITS ; 
 int HCI_FLT_TYPE_BITS ; 
 scalar_t__ get_unaligned (int /*<<< orphan*/ *) ; 
 TYPE_1__* hci_pi (struct sock*) ; 
 int hci_skb_pkt_type (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_test_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool is_filtered_packet(struct sock *sk, struct sk_buff *skb)
{
	struct hci_filter *flt;
	int flt_type, flt_event;

	/* Apply filter */
	flt = &hci_pi(sk)->filter;

	flt_type = hci_skb_pkt_type(skb) & HCI_FLT_TYPE_BITS;

	if (!test_bit(flt_type, &flt->type_mask))
		return true;

	/* Extra filter for event packets only */
	if (hci_skb_pkt_type(skb) != HCI_EVENT_PKT)
		return false;

	flt_event = (*(__u8 *)skb->data & HCI_FLT_EVENT_BITS);

	if (!hci_test_bit(flt_event, &flt->event_mask))
		return true;

	/* Check filter only when opcode is set */
	if (!flt->opcode)
		return false;

	if (flt_event == HCI_EV_CMD_COMPLETE &&
	    flt->opcode != get_unaligned((__le16 *)(skb->data + 3)))
		return true;

	if (flt_event == HCI_EV_CMD_STATUS &&
	    flt->opcode != get_unaligned((__le16 *)(skb->data + 4)))
		return true;

	return false;
}