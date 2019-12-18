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
struct hci_dev {int /*<<< orphan*/  (* notify ) (struct hci_dev*,int /*<<< orphan*/ ) ;} ;
struct hci_conn {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; struct hci_dev* hdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONN_PARAM_REMOVAL_PEND ; 
 int /*<<< orphan*/  HCI_NOTIFY_CONN_DEL ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_chan_list_flush (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_del_sysfs (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_hash_del (struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_params_del (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_conn_cleanup(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;

	if (test_bit(HCI_CONN_PARAM_REMOVAL_PEND, &conn->flags))
		hci_conn_params_del(conn->hdev, &conn->dst, conn->dst_type);

	hci_chan_list_flush(conn);

	hci_conn_hash_del(hdev, conn);

	if (hdev->notify)
		hdev->notify(hdev, HCI_NOTIFY_CONN_DEL);

	hci_conn_del_sysfs(conn);

	debugfs_remove_recursive(conn->debugfs);

	hci_dev_put(hdev);

	hci_conn_put(conn);
}