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
struct hci_dev {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EBUSY ; 
 int ENETDOWN ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCI_UNCONFIGURED ; 
 int /*<<< orphan*/  HCI_UP ; 
 int /*<<< orphan*/  HCI_USER_CHANNEL ; 
 int hci_dev_do_reset (struct hci_dev*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_dev_reset(__u16 dev)
{
	struct hci_dev *hdev;
	int err;

	hdev = hci_dev_get(dev);
	if (!hdev)
		return -ENODEV;

	if (!test_bit(HCI_UP, &hdev->flags)) {
		err = -ENETDOWN;
		goto done;
	}

	if (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) {
		err = -EBUSY;
		goto done;
	}

	if (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) {
		err = -EOPNOTSUPP;
		goto done;
	}

	err = hci_dev_do_reset(hdev);

done:
	hci_dev_put(hdev);
	return err;
}