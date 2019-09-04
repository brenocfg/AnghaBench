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
struct hci_ev_key_refresh_complete {scalar_t__ status; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ type; scalar_t__ state; int /*<<< orphan*/  disc_timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  pending_sec_level; int /*<<< orphan*/  sec_level; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 int /*<<< orphan*/  HCI_DISCONN_TIMEOUT ; 
 int /*<<< orphan*/  HCI_ERROR_AUTH_FAILURE ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_auth_cfm (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_disconnect (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_key_refresh_complete_evt(struct hci_dev *hdev,
					 struct sk_buff *skb)
{
	struct hci_ev_key_refresh_complete *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x handle 0x%4.4x", hdev->name, ev->status,
	       __le16_to_cpu(ev->handle));

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (!conn)
		goto unlock;

	/* For BR/EDR the necessary steps are taken through the
	 * auth_complete event.
	 */
	if (conn->type != LE_LINK)
		goto unlock;

	if (!ev->status)
		conn->sec_level = conn->pending_sec_level;

	clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);

	if (ev->status && conn->state == BT_CONNECTED) {
		hci_disconnect(conn, HCI_ERROR_AUTH_FAILURE);
		hci_conn_drop(conn);
		goto unlock;
	}

	if (conn->state == BT_CONFIG) {
		if (!ev->status)
			conn->state = BT_CONNECTED;

		hci_connect_cfm(conn, ev->status);
		hci_conn_drop(conn);
	} else {
		hci_auth_cfm(conn, ev->status);

		hci_conn_hold(conn);
		conn->disc_timeout = HCI_DISCONN_TIMEOUT;
		hci_conn_drop(conn);
	}

unlock:
	hci_dev_unlock(hdev);
}