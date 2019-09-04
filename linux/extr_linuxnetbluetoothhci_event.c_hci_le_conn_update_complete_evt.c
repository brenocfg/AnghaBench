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
struct hci_ev_le_conn_update_complete {int /*<<< orphan*/  supervision_timeout; int /*<<< orphan*/  latency; int /*<<< orphan*/  interval; int /*<<< orphan*/  handle; scalar_t__ status; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {void* le_supv_timeout; void* le_conn_latency; void* le_conn_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_le_conn_update_complete_evt(struct hci_dev *hdev,
					    struct sk_buff *skb)
{
	struct hci_ev_le_conn_update_complete *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	if (ev->status)
		return;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (conn) {
		conn->le_conn_interval = le16_to_cpu(ev->interval);
		conn->le_conn_latency = le16_to_cpu(ev->latency);
		conn->le_supv_timeout = le16_to_cpu(ev->supervision_timeout);
	}

	hci_dev_unlock(hdev);
}