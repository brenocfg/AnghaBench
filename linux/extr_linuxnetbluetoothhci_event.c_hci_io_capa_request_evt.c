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
struct hci_ev_io_capa_request {int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_io_capability_reply {int capability; int authentication; int /*<<< orphan*/  reason; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  oob_data; } ;
struct hci_cp_io_capability_neg_reply {int capability; int authentication; int /*<<< orphan*/  reason; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  oob_data; } ;
struct hci_conn {int remote_auth; int io_capability; int auth_type; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int HCI_AT_NO_BONDING ; 
 int HCI_AT_NO_BONDING_MITM ; 
 int /*<<< orphan*/  HCI_BONDABLE ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_INITIATOR ; 
 int /*<<< orphan*/  HCI_ERROR_PAIRING_NOT_ALLOWED ; 
 int HCI_IO_DISPLAY_YESNO ; 
 int HCI_IO_NO_INPUT_OUTPUT ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_IO_CAPABILITY_NEG_REPLY ; 
 int /*<<< orphan*/  HCI_OP_IO_CAPABILITY_REPLY ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bredr_oob_data_present (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hci_get_auth_req (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_io_capability_reply*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_io_capa_request_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_io_capa_request *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	if (!conn)
		goto unlock;

	hci_conn_hold(conn);

	if (!hci_dev_test_flag(hdev, HCI_MGMT))
		goto unlock;

	/* Allow pairing if we're pairable, the initiators of the
	 * pairing or if the remote is not requesting bonding.
	 */
	if (hci_dev_test_flag(hdev, HCI_BONDABLE) ||
	    test_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags) ||
	    (conn->remote_auth & ~0x01) == HCI_AT_NO_BONDING) {
		struct hci_cp_io_capability_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		/* Change the IO capability from KeyboardDisplay
		 * to DisplayYesNo as it is not supported by BT spec. */
		cp.capability = (conn->io_capability == 0x04) ?
				HCI_IO_DISPLAY_YESNO : conn->io_capability;

		/* If we are initiators, there is no remote information yet */
		if (conn->remote_auth == 0xff) {
			/* Request MITM protection if our IO caps allow it
			 * except for the no-bonding case.
			 */
			if (conn->io_capability != HCI_IO_NO_INPUT_OUTPUT &&
			    conn->auth_type != HCI_AT_NO_BONDING)
				conn->auth_type |= 0x01;
		} else {
			conn->auth_type = hci_get_auth_req(conn);
		}

		/* If we're not bondable, force one of the non-bondable
		 * authentication requirement values.
		 */
		if (!hci_dev_test_flag(hdev, HCI_BONDABLE))
			conn->auth_type &= HCI_AT_NO_BONDING_MITM;

		cp.authentication = conn->auth_type;
		cp.oob_data = bredr_oob_data_present(conn);

		hci_send_cmd(hdev, HCI_OP_IO_CAPABILITY_REPLY,
			     sizeof(cp), &cp);
	} else {
		struct hci_cp_io_capability_neg_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		cp.reason = HCI_ERROR_PAIRING_NOT_ALLOWED;

		hci_send_cmd(hdev, HCI_OP_IO_CAPABILITY_NEG_REPLY,
			     sizeof(cp), &cp);
	}

unlock:
	hci_dev_unlock(hdev);
}