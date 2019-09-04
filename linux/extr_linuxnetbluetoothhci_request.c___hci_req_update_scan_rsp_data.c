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
typedef  void* u8 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {void* scan_rsp_data_len; int /*<<< orphan*/  scan_rsp_data; } ;
struct hci_cp_le_set_scan_rsp_data {void* length; int /*<<< orphan*/  data; int /*<<< orphan*/  frag_pref; int /*<<< orphan*/  operation; scalar_t__ handle; } ;
struct hci_cp_le_set_ext_scan_rsp_data {void* length; int /*<<< orphan*/  data; int /*<<< orphan*/  frag_pref; int /*<<< orphan*/  operation; scalar_t__ handle; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_SCAN_RSP_DATA ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_SCAN_RSP_DATA ; 
 int /*<<< orphan*/  LE_SET_ADV_DATA_NO_FRAG ; 
 int /*<<< orphan*/  LE_SET_ADV_DATA_OP_COMPLETE ; 
 void* create_default_scan_rsp_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 void* create_instance_scan_rsp_data (struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_le_set_scan_rsp_data*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_set_scan_rsp_data*,int /*<<< orphan*/ ,int) ; 

void __hci_req_update_scan_rsp_data(struct hci_request *req, u8 instance)
{
	struct hci_dev *hdev = req->hdev;
	u8 len;

	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		return;

	if (ext_adv_capable(hdev)) {
		struct hci_cp_le_set_ext_scan_rsp_data cp;

		memset(&cp, 0, sizeof(cp));

		if (instance)
			len = create_instance_scan_rsp_data(hdev, instance,
							    cp.data);
		else
			len = create_default_scan_rsp_data(hdev, cp.data);

		if (hdev->scan_rsp_data_len == len &&
		    !memcmp(cp.data, hdev->scan_rsp_data, len))
			return;

		memcpy(hdev->scan_rsp_data, cp.data, sizeof(cp.data));
		hdev->scan_rsp_data_len = len;

		cp.handle = 0;
		cp.length = len;
		cp.operation = LE_SET_ADV_DATA_OP_COMPLETE;
		cp.frag_pref = LE_SET_ADV_DATA_NO_FRAG;

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_RSP_DATA, sizeof(cp),
			    &cp);
	} else {
		struct hci_cp_le_set_scan_rsp_data cp;

		memset(&cp, 0, sizeof(cp));

		if (instance)
			len = create_instance_scan_rsp_data(hdev, instance,
							    cp.data);
		else
			len = create_default_scan_rsp_data(hdev, cp.data);

		if (hdev->scan_rsp_data_len == len &&
		    !memcmp(cp.data, hdev->scan_rsp_data, len))
			return;

		memcpy(hdev->scan_rsp_data, cp.data, sizeof(cp.data));
		hdev->scan_rsp_data_len = len;

		cp.length = len;

		hci_req_add(req, HCI_OP_LE_SET_SCAN_RSP_DATA, sizeof(cp), &cp);
	}
}