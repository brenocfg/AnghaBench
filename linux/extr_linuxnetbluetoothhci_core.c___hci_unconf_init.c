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
struct hci_dev {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_QUIRK_RAW_DEVICE ; 
 int /*<<< orphan*/  HCI_SETUP ; 
 int __hci_req_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_debugfs_create_basic (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_init0_req ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __hci_unconf_init(struct hci_dev *hdev)
{
	int err;

	if (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		return 0;

	err = __hci_req_sync(hdev, hci_init0_req, 0, HCI_INIT_TIMEOUT, NULL);
	if (err < 0)
		return err;

	if (hci_dev_test_flag(hdev, HCI_SETUP))
		hci_debugfs_create_basic(hdev);

	return 0;
}