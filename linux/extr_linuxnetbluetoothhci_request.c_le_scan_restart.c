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
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;
struct hci_cp_le_set_scan_enable {void* filter_dup; void* enable; } ;
struct hci_cp_le_set_ext_scan_enable {void* filter_dup; void* enable; } ;
typedef  int /*<<< orphan*/  ext_enable_cp ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_SCAN_ENABLE ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_SCAN_ENABLE ; 
 void* LE_SCAN_ENABLE ; 
 void* LE_SCAN_FILTER_DUP_ENABLE ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_le_set_scan_enable*) ; 
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 
 int /*<<< orphan*/  memset (struct hci_cp_le_set_scan_enable*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_ext_scan (struct hci_dev*) ; 

__attribute__((used)) static int le_scan_restart(struct hci_request *req, unsigned long opt)
{
	struct hci_dev *hdev = req->hdev;

	/* If controller is not scanning we are done. */
	if (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
		return 0;

	hci_req_add_le_scan_disable(req);

	if (use_ext_scan(hdev)) {
		struct hci_cp_le_set_ext_scan_enable ext_enable_cp;

		memset(&ext_enable_cp, 0, sizeof(ext_enable_cp));
		ext_enable_cp.enable = LE_SCAN_ENABLE;
		ext_enable_cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_ENABLE,
			    sizeof(ext_enable_cp), &ext_enable_cp);
	} else {
		struct hci_cp_le_set_scan_enable cp;

		memset(&cp, 0, sizeof(cp));
		cp.enable = LE_SCAN_ENABLE;
		cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_ENABLE, sizeof(cp), &cp);
	}

	return 0;
}