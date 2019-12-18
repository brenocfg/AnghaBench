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
struct hci_dev {int id; int /*<<< orphan*/  le_resolv_list; int /*<<< orphan*/  le_white_list; int /*<<< orphan*/  whitelist; int /*<<< orphan*/  blacklist; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  fw_info; int /*<<< orphan*/  hw_info; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  dev; scalar_t__ rfkill; int /*<<< orphan*/  mgmt_pending; int /*<<< orphan*/  flags; int /*<<< orphan*/  power_on; int /*<<< orphan*/  list; int /*<<< orphan*/  bus; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HCI_CONFIG ; 
 int /*<<< orphan*/  HCI_DEV_UNREG ; 
 int /*<<< orphan*/  HCI_INIT ; 
 int /*<<< orphan*/  HCI_SETUP ; 
 int /*<<< orphan*/  HCI_UNREGISTER ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_adv_instances_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_bdaddr_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_params_clear_all (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_do_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_list_lock ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_filter_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_index_ida ; 
 int /*<<< orphan*/  hci_link_keys_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_remote_oob_data_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_smp_irks_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_smp_ltks_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_sock_dev_event (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_uuids_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_index_removed (struct hci_dev*) ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void hci_unregister_dev(struct hci_dev *hdev)
{
	int id;

	BT_DBG("%p name %s bus %d", hdev, hdev->name, hdev->bus);

	hci_dev_set_flag(hdev, HCI_UNREGISTER);

	id = hdev->id;

	write_lock(&hci_dev_list_lock);
	list_del(&hdev->list);
	write_unlock(&hci_dev_list_lock);

	cancel_work_sync(&hdev->power_on);

	hci_dev_do_close(hdev);

	if (!test_bit(HCI_INIT, &hdev->flags) &&
	    !hci_dev_test_flag(hdev, HCI_SETUP) &&
	    !hci_dev_test_flag(hdev, HCI_CONFIG)) {
		hci_dev_lock(hdev);
		mgmt_index_removed(hdev);
		hci_dev_unlock(hdev);
	}

	/* mgmt_index_removed should take care of emptying the
	 * pending list */
	BUG_ON(!list_empty(&hdev->mgmt_pending));

	hci_sock_dev_event(hdev, HCI_DEV_UNREG);

	if (hdev->rfkill) {
		rfkill_unregister(hdev->rfkill);
		rfkill_destroy(hdev->rfkill);
	}

	device_del(&hdev->dev);

	debugfs_remove_recursive(hdev->debugfs);
	kfree_const(hdev->hw_info);
	kfree_const(hdev->fw_info);

	destroy_workqueue(hdev->workqueue);
	destroy_workqueue(hdev->req_workqueue);

	hci_dev_lock(hdev);
	hci_bdaddr_list_clear(&hdev->blacklist);
	hci_bdaddr_list_clear(&hdev->whitelist);
	hci_uuids_clear(hdev);
	hci_link_keys_clear(hdev);
	hci_smp_ltks_clear(hdev);
	hci_smp_irks_clear(hdev);
	hci_remote_oob_data_clear(hdev);
	hci_adv_instances_clear(hdev);
	hci_bdaddr_list_clear(&hdev->le_white_list);
	hci_bdaddr_list_clear(&hdev->le_resolv_list);
	hci_conn_params_clear_all(hdev);
	hci_discovery_filter_clear(hdev);
	hci_dev_unlock(hdev);

	hci_dev_put(hdev);

	ida_simple_remove(&hci_index_ida, id);
}