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
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int minor_class; int major_class; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  cod ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_LIMITED_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_OP_WRITE_CLASS_OF_DEV ; 
 int /*<<< orphan*/  HCI_SERVICE_CACHE ; 
 int get_service_classes (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 

void __hci_req_update_class(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	u8 cod[3];

	BT_DBG("%s", hdev->name);

	if (!hdev_is_powered(hdev))
		return;

	if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		return;

	if (hci_dev_test_flag(hdev, HCI_SERVICE_CACHE))
		return;

	cod[0] = hdev->minor_class;
	cod[1] = hdev->major_class;
	cod[2] = get_service_classes(hdev);

	if (hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE))
		cod[1] |= 0x20;

	if (memcmp(cod, hdev->dev_class, 3) == 0)
		return;

	hci_req_add(req, HCI_OP_WRITE_CLASS_OF_DEV, sizeof(cod), cod);
}