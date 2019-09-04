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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_hold (struct hci_dev*) ; 

void hci_conn_add_sysfs(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;

	BT_DBG("conn %p", conn);

	dev_set_name(&conn->dev, "%s:%d", hdev->name, conn->handle);

	if (device_add(&conn->dev) < 0) {
		bt_dev_err(hdev, "failed to register connection device");
		return;
	}

	hci_dev_hold(hdev);
}