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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_disconn_complete {int /*<<< orphan*/  reason; scalar_t__ status; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  pend_le_conns; int /*<<< orphan*/  name; } ;
struct hci_conn_params {int auto_connect; int /*<<< orphan*/  action; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
#define  HCI_AUTO_CONN_ALWAYS 130 
#define  HCI_AUTO_CONN_DIRECT 129 
#define  HCI_AUTO_CONN_LINK_LOSS 128 
 int /*<<< orphan*/  HCI_CONN_AUTH_FAILURE ; 
 int /*<<< orphan*/  HCI_CONN_FLUSH_KEY ; 
 int /*<<< orphan*/  HCI_CONN_MGMT_CONNECTED ; 
 int /*<<< orphan*/  HCI_ERROR_CONNECTION_TIMEOUT ; 
 scalar_t__ LE_LINK ; 
 scalar_t__ MGMT_DEV_DISCONN_AUTH_FAILURE ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct hci_conn_params* hci_conn_params_lookup (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_disconn_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_remove_link_key (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_reenable_advertising (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_update_scan (struct hci_dev*) ; 
 scalar_t__ hci_to_mgmt_reason (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_device_disconnected (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mgmt_disconnect_failed (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_disconn_complete_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_disconn_complete *ev = (void *) skb->data;
	u8 reason;
	struct hci_conn_params *params;
	struct hci_conn *conn;
	bool mgmt_connected;
	u8 type;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (!conn)
		goto unlock;

	if (ev->status) {
		mgmt_disconnect_failed(hdev, &conn->dst, conn->type,
				       conn->dst_type, ev->status);
		goto unlock;
	}

	conn->state = BT_CLOSED;

	mgmt_connected = test_and_clear_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags);

	if (test_bit(HCI_CONN_AUTH_FAILURE, &conn->flags))
		reason = MGMT_DEV_DISCONN_AUTH_FAILURE;
	else
		reason = hci_to_mgmt_reason(ev->reason);

	mgmt_device_disconnected(hdev, &conn->dst, conn->type, conn->dst_type,
				reason, mgmt_connected);

	if (conn->type == ACL_LINK) {
		if (test_bit(HCI_CONN_FLUSH_KEY, &conn->flags))
			hci_remove_link_key(hdev, &conn->dst);

		hci_req_update_scan(hdev);
	}

	params = hci_conn_params_lookup(hdev, &conn->dst, conn->dst_type);
	if (params) {
		switch (params->auto_connect) {
		case HCI_AUTO_CONN_LINK_LOSS:
			if (ev->reason != HCI_ERROR_CONNECTION_TIMEOUT)
				break;
			/* Fall through */

		case HCI_AUTO_CONN_DIRECT:
		case HCI_AUTO_CONN_ALWAYS:
			list_del_init(&params->action);
			list_add(&params->action, &hdev->pend_le_conns);
			hci_update_background_scan(hdev);
			break;

		default:
			break;
		}
	}

	type = conn->type;

	hci_disconn_cfm(conn, ev->reason);
	hci_conn_del(conn);

	/* Re-enable advertising if necessary, since it might
	 * have been disabled by the connection. From the
	 * HCI_LE_Set_Advertise_Enable command description in
	 * the core specification (v4.0):
	 * "The Controller shall continue advertising until the Host
	 * issues an LE_Set_Advertise_Enable command with
	 * Advertising_Enable set to 0x00 (Advertising is disabled)
	 * or until a connection is created or until the Advertising
	 * is timed out due to Directed Advertising."
	 */
	if (type == LE_LINK)
		hci_req_reenable_advertising(hdev);

unlock:
	hci_dev_unlock(hdev);
}