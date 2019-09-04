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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct hci_dev {scalar_t__ sco_cnt; int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  sent; int /*<<< orphan*/  data_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sk_buff*,...) ; 
 int /*<<< orphan*/  ESCO_LINK ; 
 int /*<<< orphan*/  hci_conn_num (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_low_sent (struct hci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_send_frame (struct hci_dev*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_sched_esco(struct hci_dev *hdev)
{
	struct hci_conn *conn;
	struct sk_buff *skb;
	int quote;

	BT_DBG("%s", hdev->name);

	if (!hci_conn_num(hdev, ESCO_LINK))
		return;

	while (hdev->sco_cnt && (conn = hci_low_sent(hdev, ESCO_LINK,
						     &quote))) {
		while (quote-- && (skb = skb_dequeue(&conn->data_q))) {
			BT_DBG("skb %p len %d", skb, skb->len);
			hci_send_frame(hdev, skb);

			conn->sent++;
			if (conn->sent == ~0)
				conn->sent = 0;
		}
	}
}