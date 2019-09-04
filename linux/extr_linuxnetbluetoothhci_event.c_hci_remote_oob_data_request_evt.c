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
struct oob_data {int /*<<< orphan*/  rand192; int /*<<< orphan*/  hash192; int /*<<< orphan*/  rand256; int /*<<< orphan*/  hash256; } ;
struct hci_ev_remote_oob_data_request {int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_remote_oob_ext_data_reply {int /*<<< orphan*/  rand; int /*<<< orphan*/  hash; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  rand256; int /*<<< orphan*/  hash256; int /*<<< orphan*/  rand192; int /*<<< orphan*/  hash192; } ;
struct hci_cp_remote_oob_data_reply {int /*<<< orphan*/  rand; int /*<<< orphan*/  hash; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  rand256; int /*<<< orphan*/  hash256; int /*<<< orphan*/  rand192; int /*<<< orphan*/  hash192; } ;
struct hci_cp_remote_oob_data_neg_reply {int /*<<< orphan*/  rand; int /*<<< orphan*/  hash; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  rand256; int /*<<< orphan*/  hash256; int /*<<< orphan*/  rand192; int /*<<< orphan*/  hash192; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_REMOTE_OOB_DATA_NEG_REPLY ; 
 int /*<<< orphan*/  HCI_OP_REMOTE_OOB_DATA_REPLY ; 
 int /*<<< orphan*/  HCI_OP_REMOTE_OOB_EXT_DATA_REPLY ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bredr_sc_enabled (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct oob_data* hci_find_remote_oob_data (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_remote_oob_ext_data_reply*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hci_remote_oob_data_request_evt(struct hci_dev *hdev,
					    struct sk_buff *skb)
{
	struct hci_ev_remote_oob_data_request *ev = (void *) skb->data;
	struct oob_data *data;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	if (!hci_dev_test_flag(hdev, HCI_MGMT))
		goto unlock;

	data = hci_find_remote_oob_data(hdev, &ev->bdaddr, BDADDR_BREDR);
	if (!data) {
		struct hci_cp_remote_oob_data_neg_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		hci_send_cmd(hdev, HCI_OP_REMOTE_OOB_DATA_NEG_REPLY,
			     sizeof(cp), &cp);
		goto unlock;
	}

	if (bredr_sc_enabled(hdev)) {
		struct hci_cp_remote_oob_ext_data_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		if (hci_dev_test_flag(hdev, HCI_SC_ONLY)) {
			memset(cp.hash192, 0, sizeof(cp.hash192));
			memset(cp.rand192, 0, sizeof(cp.rand192));
		} else {
			memcpy(cp.hash192, data->hash192, sizeof(cp.hash192));
			memcpy(cp.rand192, data->rand192, sizeof(cp.rand192));
		}
		memcpy(cp.hash256, data->hash256, sizeof(cp.hash256));
		memcpy(cp.rand256, data->rand256, sizeof(cp.rand256));

		hci_send_cmd(hdev, HCI_OP_REMOTE_OOB_EXT_DATA_REPLY,
			     sizeof(cp), &cp);
	} else {
		struct hci_cp_remote_oob_data_reply cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		memcpy(cp.hash, data->hash192, sizeof(cp.hash));
		memcpy(cp.rand, data->rand192, sizeof(cp.rand));

		hci_send_cmd(hdev, HCI_OP_REMOTE_OOB_DATA_REPLY,
			     sizeof(cp), &cp);
	}

unlock:
	hci_dev_unlock(hdev);
}