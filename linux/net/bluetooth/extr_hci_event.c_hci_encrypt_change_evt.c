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
struct hci_request {int dummy; } ;
struct hci_ev_encrypt_change {scalar_t__ status; int encrypt; int /*<<< orphan*/  handle; } ;
struct hci_dev {int* commands; int* le_features; int /*<<< orphan*/  auth_payload_timeout; int /*<<< orphan*/  name; } ;
struct hci_cp_write_auth_payload_to {void* timeout; void* handle; } ;
struct hci_cp_read_enc_key_size {void* handle; } ;
struct hci_conn {scalar_t__ key_type; scalar_t__ type; scalar_t__ state; int /*<<< orphan*/  hdev; int /*<<< orphan*/  handle; int /*<<< orphan*/  flags; void* enc_key_size; int /*<<< orphan*/  pending_sec_level; int /*<<< orphan*/  sec_level; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_CONN_AES_CCM ; 
 int /*<<< orphan*/  HCI_CONN_AUTH ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_FAILURE ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 int /*<<< orphan*/  HCI_CONN_FIPS ; 
 scalar_t__ HCI_ERROR_AUTH_FAILURE ; 
 scalar_t__ HCI_ERROR_PIN_OR_KEY_MISSING ; 
 int HCI_LE_PING ; 
 void* HCI_LINK_KEY_SIZE ; 
 scalar_t__ HCI_LK_AUTH_COMBINATION_P256 ; 
 int /*<<< orphan*/  HCI_OP_READ_ENC_KEY_SIZE ; 
 int /*<<< orphan*/  HCI_OP_WRITE_AUTH_PAYLOAD_TO ; 
 int /*<<< orphan*/  HCI_RPA_EXPIRED ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_adv_instances_set_rpa_expired (struct hci_dev*,int) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_disconnect (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_encrypt_cfm (struct hci_conn*,scalar_t__,int) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_read_enc_key_size*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 scalar_t__ hci_req_run_skb (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct hci_cp_write_auth_payload_to*) ; 
 scalar_t__ lmp_ping_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  read_enc_key_size_complete ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_encrypt_change_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_encrypt_change *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (!conn)
		goto unlock;

	if (!ev->status) {
		if (ev->encrypt) {
			/* Encryption implies authentication */
			set_bit(HCI_CONN_AUTH, &conn->flags);
			set_bit(HCI_CONN_ENCRYPT, &conn->flags);
			conn->sec_level = conn->pending_sec_level;

			/* P-256 authentication key implies FIPS */
			if (conn->key_type == HCI_LK_AUTH_COMBINATION_P256)
				set_bit(HCI_CONN_FIPS, &conn->flags);

			if ((conn->type == ACL_LINK && ev->encrypt == 0x02) ||
			    conn->type == LE_LINK)
				set_bit(HCI_CONN_AES_CCM, &conn->flags);
		} else {
			clear_bit(HCI_CONN_ENCRYPT, &conn->flags);
			clear_bit(HCI_CONN_AES_CCM, &conn->flags);
		}
	}

	/* We should disregard the current RPA and generate a new one
	 * whenever the encryption procedure fails.
	 */
	if (ev->status && conn->type == LE_LINK) {
		hci_dev_set_flag(hdev, HCI_RPA_EXPIRED);
		hci_adv_instances_set_rpa_expired(hdev, true);
	}

	clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);

	if (ev->status && conn->state == BT_CONNECTED) {
		if (ev->status == HCI_ERROR_PIN_OR_KEY_MISSING)
			set_bit(HCI_CONN_AUTH_FAILURE, &conn->flags);

		hci_disconnect(conn, HCI_ERROR_AUTH_FAILURE);
		hci_conn_drop(conn);
		goto unlock;
	}

	/* In Secure Connections Only mode, do not allow any connections
	 * that are not encrypted with AES-CCM using a P-256 authenticated
	 * combination key.
	 */
	if (hci_dev_test_flag(hdev, HCI_SC_ONLY) &&
	    (!test_bit(HCI_CONN_AES_CCM, &conn->flags) ||
	     conn->key_type != HCI_LK_AUTH_COMBINATION_P256)) {
		hci_connect_cfm(conn, HCI_ERROR_AUTH_FAILURE);
		hci_conn_drop(conn);
		goto unlock;
	}

	/* Try reading the encryption key size for encrypted ACL links */
	if (!ev->status && ev->encrypt && conn->type == ACL_LINK) {
		struct hci_cp_read_enc_key_size cp;
		struct hci_request req;

		/* Only send HCI_Read_Encryption_Key_Size if the
		 * controller really supports it. If it doesn't, assume
		 * the default size (16).
		 */
		if (!(hdev->commands[20] & 0x10)) {
			conn->enc_key_size = HCI_LINK_KEY_SIZE;
			goto notify;
		}

		hci_req_init(&req, hdev);

		cp.handle = cpu_to_le16(conn->handle);
		hci_req_add(&req, HCI_OP_READ_ENC_KEY_SIZE, sizeof(cp), &cp);

		if (hci_req_run_skb(&req, read_enc_key_size_complete)) {
			bt_dev_err(hdev, "sending read key size failed");
			conn->enc_key_size = HCI_LINK_KEY_SIZE;
			goto notify;
		}

		goto unlock;
	}

	/* Set the default Authenticated Payload Timeout after
	 * an LE Link is established. As per Core Spec v5.0, Vol 2, Part B
	 * Section 3.3, the HCI command WRITE_AUTH_PAYLOAD_TIMEOUT should be
	 * sent when the link is active and Encryption is enabled, the conn
	 * type can be either LE or ACL and controller must support LMP Ping.
	 * Ensure for AES-CCM encryption as well.
	 */
	if (test_bit(HCI_CONN_ENCRYPT, &conn->flags) &&
	    test_bit(HCI_CONN_AES_CCM, &conn->flags) &&
	    ((conn->type == ACL_LINK && lmp_ping_capable(hdev)) ||
	     (conn->type == LE_LINK && (hdev->le_features[0] & HCI_LE_PING)))) {
		struct hci_cp_write_auth_payload_to cp;

		cp.handle = cpu_to_le16(conn->handle);
		cp.timeout = cpu_to_le16(hdev->auth_payload_timeout);
		hci_send_cmd(conn->hdev, HCI_OP_WRITE_AUTH_PAYLOAD_TO,
			     sizeof(cp), &cp);
	}

notify:
	if (conn->state == BT_CONFIG) {
		if (!ev->status)
			conn->state = BT_CONNECTED;

		hci_connect_cfm(conn, ev->status);
		hci_conn_drop(conn);
	} else
		hci_encrypt_cfm(conn, ev->status, ev->encrypt);

unlock:
	hci_dev_unlock(hdev);
}