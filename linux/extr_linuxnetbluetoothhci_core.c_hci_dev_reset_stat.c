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
struct hci_dev_stats {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  stat; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCI_UNCONFIGURED ; 
 int /*<<< orphan*/  HCI_USER_CHANNEL ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int hci_dev_reset_stat(__u16 dev)
{
	struct hci_dev *hdev;
	int ret = 0;

	hdev = hci_dev_get(dev);
	if (!hdev)
		return -ENODEV;

	if (hci_dev_test_flag(hdev, HCI_USER_CHANNEL)) {
		ret = -EBUSY;
		goto done;
	}

	if (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) {
		ret = -EOPNOTSUPP;
		goto done;
	}

	memset(&hdev->stat, 0, sizeof(struct hci_dev_stats));

done:
	hci_dev_put(hdev);
	return ret;
}