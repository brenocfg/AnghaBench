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
struct hci_ev_auth_complete {scalar_t__ status; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_set_conn_encrypt {int encrypt; int /*<<< orphan*/  handle; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  disc_timeout; int /*<<< orphan*/  pending_sec_level; int /*<<< orphan*/  sec_level; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_CONN_AUTH ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_FAILURE ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_PEND ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 int /*<<< orphan*/  HCI_CONN_REAUTH_PEND ; 
 int /*<<< orphan*/  HCI_DISCONN_TIMEOUT ; 
 scalar_t__ HCI_ERROR_PIN_OR_KEY_MISSING ; 
 int /*<<< orphan*/  HCI_OP_SET_CONN_ENCRYPT ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_auth_cfm (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 scalar_t__ hci_conn_ssp_enabled (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_encrypt_cfm (struct hci_conn*,scalar_t__,int) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_set_conn_encrypt*) ; 
 int /*<<< orphan*/  mgmt_auth_failed (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_auth_complete_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_auth_complete *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (!conn)
		goto unlock;

	if (!ev->status) {
		clear_bit(HCI_CONN_AUTH_FAILURE, &conn->flags);

		if (!hci_conn_ssp_enabled(conn) &&
		    test_bit(HCI_CONN_REAUTH_PEND, &conn->flags)) {
			bt_dev_info(hdev, "re-auth of legacy device is not possible.");
		} else {
			set_bit(HCI_CONN_AUTH, &conn->flags);
			conn->sec_level = conn->pending_sec_level;
		}
	} else {
		if (ev->status == HCI_ERROR_PIN_OR_KEY_MISSING)
			set_bit(HCI_CONN_AUTH_FAILURE, &conn->flags);

		mgmt_auth_failed(conn, ev->status);
	}

	clear_bit(HCI_CONN_AUTH_PEND, &conn->flags);
	clear_bit(HCI_CONN_REAUTH_PEND, &conn->flags);

	if (conn->state == BT_CONFIG) {
		if (!ev->status && hci_conn_ssp_enabled(conn)) {
			struct hci_cp_set_conn_encrypt cp;
			cp.handle  = ev->handle;
			cp.encrypt = 0x01;
			hci_send_cmd(hdev, HCI_OP_SET_CONN_ENCRYPT, sizeof(cp),
				     &cp);
		} else {
			conn->state = BT_CONNECTED;
			hci_connect_cfm(conn, ev->status);
			hci_conn_drop(conn);
		}
	} else {
		hci_auth_cfm(conn, ev->status);

		hci_conn_hold(conn);
		conn->disc_timeout = HCI_DISCONN_TIMEOUT;
		hci_conn_drop(conn);
	}

	if (test_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags)) {
		if (!ev->status) {
			struct hci_cp_set_conn_encrypt cp;
			cp.handle  = ev->handle;
			cp.encrypt = 0x01;
			hci_send_cmd(hdev, HCI_OP_SET_CONN_ENCRYPT, sizeof(cp),
				     &cp);
		} else {
			clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);
			hci_encrypt_cfm(conn, ev->status, 0x00);
		}
	}

unlock:
	hci_dev_unlock(hdev);
}