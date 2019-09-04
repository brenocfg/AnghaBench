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
struct hci_dev {int dev_type; int id; void* req_workqueue; void* workqueue; int /*<<< orphan*/  power_on; int /*<<< orphan*/  quirks; int /*<<< orphan*/  list; int /*<<< orphan*/ * rfkill; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  bus; int /*<<< orphan*/  send; int /*<<< orphan*/  close; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HCI_AMP 129 
 int /*<<< orphan*/  HCI_AUTO_OFF ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_DEV_REG ; 
#define  HCI_PRIMARY 128 
 int /*<<< orphan*/  HCI_QUIRK_RAW_DEVICE ; 
 int /*<<< orphan*/  HCI_RFKILLED ; 
 int /*<<< orphan*/  HCI_SETUP ; 
 int /*<<< orphan*/  HCI_UNCONFIGURED ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFKILL_TYPE_BLUETOOTH ; 
 int /*<<< orphan*/  WQ_HIGHPRI ; 
 void* alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_debugfs ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_hold (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_list ; 
 int /*<<< orphan*/  hci_dev_list_lock ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_index_ida ; 
 int /*<<< orphan*/  hci_leds_init (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_rfkill_ops ; 
 int /*<<< orphan*/  hci_sock_dev_event (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rfkill_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct hci_dev*) ; 
 scalar_t__ rfkill_blocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ rfkill_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int hci_register_dev(struct hci_dev *hdev)
{
	int id, error;

	if (!hdev->open || !hdev->close || !hdev->send)
		return -EINVAL;

	/* Do not allow HCI_AMP devices to register at index 0,
	 * so the index can be used as the AMP controller ID.
	 */
	switch (hdev->dev_type) {
	case HCI_PRIMARY:
		id = ida_simple_get(&hci_index_ida, 0, 0, GFP_KERNEL);
		break;
	case HCI_AMP:
		id = ida_simple_get(&hci_index_ida, 1, 0, GFP_KERNEL);
		break;
	default:
		return -EINVAL;
	}

	if (id < 0)
		return id;

	sprintf(hdev->name, "hci%d", id);
	hdev->id = id;

	BT_DBG("%p name %s bus %d", hdev, hdev->name, hdev->bus);

	hdev->workqueue = alloc_ordered_workqueue("%s", WQ_HIGHPRI, hdev->name);
	if (!hdev->workqueue) {
		error = -ENOMEM;
		goto err;
	}

	hdev->req_workqueue = alloc_ordered_workqueue("%s", WQ_HIGHPRI,
						      hdev->name);
	if (!hdev->req_workqueue) {
		destroy_workqueue(hdev->workqueue);
		error = -ENOMEM;
		goto err;
	}

	if (!IS_ERR_OR_NULL(bt_debugfs))
		hdev->debugfs = debugfs_create_dir(hdev->name, bt_debugfs);

	dev_set_name(&hdev->dev, "%s", hdev->name);

	error = device_add(&hdev->dev);
	if (error < 0)
		goto err_wqueue;

	hci_leds_init(hdev);

	hdev->rfkill = rfkill_alloc(hdev->name, &hdev->dev,
				    RFKILL_TYPE_BLUETOOTH, &hci_rfkill_ops,
				    hdev);
	if (hdev->rfkill) {
		if (rfkill_register(hdev->rfkill) < 0) {
			rfkill_destroy(hdev->rfkill);
			hdev->rfkill = NULL;
		}
	}

	if (hdev->rfkill && rfkill_blocked(hdev->rfkill))
		hci_dev_set_flag(hdev, HCI_RFKILLED);

	hci_dev_set_flag(hdev, HCI_SETUP);
	hci_dev_set_flag(hdev, HCI_AUTO_OFF);

	if (hdev->dev_type == HCI_PRIMARY) {
		/* Assume BR/EDR support until proven otherwise (such as
		 * through reading supported features during init.
		 */
		hci_dev_set_flag(hdev, HCI_BREDR_ENABLED);
	}

	write_lock(&hci_dev_list_lock);
	list_add(&hdev->list, &hci_dev_list);
	write_unlock(&hci_dev_list_lock);

	/* Devices that are marked for raw-only usage are unconfigured
	 * and should not be included in normal operation.
	 */
	if (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		hci_dev_set_flag(hdev, HCI_UNCONFIGURED);

	hci_sock_dev_event(hdev, HCI_DEV_REG);
	hci_dev_hold(hdev);

	queue_work(hdev->req_workqueue, &hdev->power_on);

	return id;

err_wqueue:
	destroy_workqueue(hdev->workqueue);
	destroy_workqueue(hdev->req_workqueue);
err:
	ida_simple_remove(&hci_index_ida, hdev->id);

	return error;
}