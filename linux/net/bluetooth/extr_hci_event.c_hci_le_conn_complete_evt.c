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
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_le_conn_complete {int /*<<< orphan*/  supervision_timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  interval; int /*<<< orphan*/  handle; int /*<<< orphan*/  role; int /*<<< orphan*/  bdaddr_type; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  status; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_conn_complete_evt (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_le_conn_complete_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_le_conn_complete *ev = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	le_conn_complete_evt(hdev, ev->status, &ev->bdaddr, ev->bdaddr_type,
			     ev->role, le16_to_cpu(ev->handle),
			     le16_to_cpu(ev->interval),
			     le16_to_cpu(ev->latency),
			     le16_to_cpu(ev->supervision_timeout));
}