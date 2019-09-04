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
struct hci_dev {int dummy; } ;
struct hci_conn {int /*<<< orphan*/  dev; struct hci_dev* hdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_ORDER_DEV_LAST ; 
 int /*<<< orphan*/  __match_tty ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 struct device* device_find_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_move (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

void hci_conn_del_sysfs(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;

	if (!device_is_registered(&conn->dev))
		return;

	while (1) {
		struct device *dev;

		dev = device_find_child(&conn->dev, NULL, __match_tty);
		if (!dev)
			break;
		device_move(dev, NULL, DPM_ORDER_DEV_LAST);
		put_device(dev);
	}

	device_del(&conn->dev);

	hci_dev_put(hdev);
}