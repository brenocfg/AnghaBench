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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int ssp_mode; } ;
struct inquiry_entry {TYPE_1__ data; } ;
struct hci_ev_remote_ext_features {size_t page; int* features; int /*<<< orphan*/  status; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_remote_name_req {int pscan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  dst; int /*<<< orphan*/ * features; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_MGMT_CONNECTED ; 
 int /*<<< orphan*/  HCI_CONN_SC_ENABLED ; 
 int /*<<< orphan*/  HCI_CONN_SSP_ENABLED ; 
 size_t HCI_MAX_PAGES ; 
 int /*<<< orphan*/  HCI_OP_REMOTE_NAME_REQ ; 
 int LMP_HOST_SC ; 
 int LMP_HOST_SSP ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_outgoing_auth_needed (struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_remote_name_req*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (struct hci_cp_remote_name_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_device_connected (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_remote_ext_features_evt(struct hci_dev *hdev,
					struct sk_buff *skb)
{
	struct hci_ev_remote_ext_features *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (!conn)
		goto unlock;

	if (ev->page < HCI_MAX_PAGES)
		memcpy(conn->features[ev->page], ev->features, 8);

	if (!ev->status && ev->page == 0x01) {
		struct inquiry_entry *ie;

		ie = hci_inquiry_cache_lookup(hdev, &conn->dst);
		if (ie)
			ie->data.ssp_mode = (ev->features[0] & LMP_HOST_SSP);

		if (ev->features[0] & LMP_HOST_SSP) {
			set_bit(HCI_CONN_SSP_ENABLED, &conn->flags);
		} else {
			/* It is mandatory by the Bluetooth specification that
			 * Extended Inquiry Results are only used when Secure
			 * Simple Pairing is enabled, but some devices violate
			 * this.
			 *
			 * To make these devices work, the internal SSP
			 * enabled flag needs to be cleared if the remote host
			 * features do not indicate SSP support */
			clear_bit(HCI_CONN_SSP_ENABLED, &conn->flags);
		}

		if (ev->features[0] & LMP_HOST_SC)
			set_bit(HCI_CONN_SC_ENABLED, &conn->flags);
	}

	if (conn->state != BT_CONFIG)
		goto unlock;

	if (!ev->status && !test_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags)) {
		struct hci_cp_remote_name_req cp;
		memset(&cp, 0, sizeof(cp));
		bacpy(&cp.bdaddr, &conn->dst);
		cp.pscan_rep_mode = 0x02;
		hci_send_cmd(hdev, HCI_OP_REMOTE_NAME_REQ, sizeof(cp), &cp);
	} else if (!test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, NULL, 0);

	if (!hci_outgoing_auth_needed(hdev, conn)) {
		conn->state = BT_CONNECTED;
		hci_connect_cfm(conn, ev->status);
		hci_conn_drop(conn);
	}

unlock:
	hci_dev_unlock(hdev);
}