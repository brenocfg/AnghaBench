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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct hci_rp_read_enc_key_size {int /*<<< orphan*/  key_size; scalar_t__ status; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  enc_key_size; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HCI_CONN_AES_CCM ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  HCI_LINK_KEY_SIZE ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_encrypt_cfm (struct hci_conn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_enc_key_size_complete(struct hci_dev *hdev, u8 status,
				       u16 opcode, struct sk_buff *skb)
{
	const struct hci_rp_read_enc_key_size *rp;
	struct hci_conn *conn;
	u16 handle;

	BT_DBG("%s status 0x%02x", hdev->name, status);

	if (!skb || skb->len < sizeof(*rp)) {
		bt_dev_err(hdev, "invalid read key size response");
		return;
	}

	rp = (void *)skb->data;
	handle = le16_to_cpu(rp->handle);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, handle);
	if (!conn)
		goto unlock;

	/* If we fail to read the encryption key size, assume maximum
	 * (which is the same we do also when this HCI command isn't
	 * supported.
	 */
	if (rp->status) {
		bt_dev_err(hdev, "failed to read key size for handle %u",
			   handle);
		conn->enc_key_size = HCI_LINK_KEY_SIZE;
	} else {
		conn->enc_key_size = rp->key_size;
	}

	if (conn->state == BT_CONFIG) {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, 0);
		hci_conn_drop(conn);
	} else {
		u8 encrypt;

		if (!test_bit(HCI_CONN_ENCRYPT, &conn->flags))
			encrypt = 0x00;
		else if (test_bit(HCI_CONN_AES_CCM, &conn->flags))
			encrypt = 0x02;
		else
			encrypt = 0x01;

		hci_encrypt_cfm(conn, 0, encrypt);
	}

unlock:
	hci_dev_unlock(hdev);
}